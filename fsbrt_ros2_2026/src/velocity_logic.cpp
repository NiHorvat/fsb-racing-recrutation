#include <cassert>
#include <cstdint>
#include <fstream>
#include <rclcpp/logging.hpp>
#include <rclcpp/parameter.hpp>
#include <rclcpp/rclcpp.hpp>
#include <rclcpp/time.hpp>
#include <std_msgs/msg/float64.hpp>
#include <geometry_msgs/msg/point.hpp>
#include <fsbrt_ros2_2026/msg/vehicle_state.hpp>
#include <cmath>
#include <vector>
#include <utility>
#include <memory>
#include <format>
#include <iostream>

#include <nanospline/Bezier.h>
#include <Eigen/Dense>

#define MAX_VELOCITY 19.5

// braking constant A_b from settings.py
static constexpr double BRAKE_CONSTANT = 7.0;




static constexpr auto DEGREE = 5;
static_assert(DEGREE < 15);


/*
Author:

FSBRT Autonomous - Recruitment task - solution

This node determines the desired velocity for the vehicle.
It subscribes to the vehicle's state (position, angle, velocity) and the upcoming path horizon from the controller.
Based on this information, it calculates and publishes the desired velocity.
*/

class VelocityLogic : public rclcpp::Node {
public:
    VelocityLogic() : Node("velocity_logic") {
        // Subscriber
        state_sub_ = this->create_subscription<fsbrt_ros2_2026::msg::VehicleState>(
            "controller/vehicle_state", 1,
            std::bind(&VelocityLogic::stateCallback, this, std::placeholders::_1));

        // Publisher
        desired_velocity_pub_ = this->create_publisher<std_msgs::msg::Float64>(
            "velocity_logic/desired_velocity", 1);

        this->declare_parameter("max_speed_gain", 14.0);
        this->declare_parameter("base_speed", 0.7);
        this->declare_parameter("exp_a", 0.948148);
        this->declare_parameter("exp_b", 0.00317121);
        this->declare_parameter("recovery_time", 1.0);
        this->declare_parameter("brake_margin", 0.7);

        this->max_speed_gain_ = this->get_parameter("max_speed_gain").as_double();
        this->base_speed_ = this->get_parameter("base_speed").as_double();
        this->exp_a_ = this->get_parameter("exp_a").as_double();
        this->exp_b_ = this->get_parameter("exp_b").as_double();
        this->recovery_time_ = this->get_parameter("recovery_time").as_double();
        this->brake_margin_ = this->get_parameter("brake_margin").as_double();


        RCLCPP_INFO(this->get_logger(),
        "Parameters: max_speed_gain=%.3f, base_speed=%.3f, exp_a=%.6f, exp_b=%.8f, recovery_time=%.2f, brake_margin=%.2f",
        max_speed_gain_, base_speed_, exp_a_, exp_b_, recovery_time_, brake_margin_);

        //curvature_log.open("/home/nh-laptop/FSB-racing/task/fsbrt_ros2_2026/curvature.csv");
        //velocity_log.open("/home/nh-laptop/FSB-racing/task/fsbrt_ros2_2026/velocity.csv");

    }

private:


    // calculates the curvature of the spline through path[start .. start + DEGREE - 1]
    // path is the car position followed by the horizon, so start = 0 is the spline from the car
    double curvature_calculation(const std::vector<std::pair<double,double>>& path, std::size_t start) const{

        Eigen::MatrixXd matrix(DEGREE,2);

        for(auto i{0U}; i < DEGREE; i++){
            matrix(i,0) = path[start + i].first;
            matrix(i,1) = path[start + i].second;
        }
        nanospline::Bezier<double, 2, DEGREE - 1> curve;
        curve.set_control_points(matrix);

        auto curvature = std::abs(curve.get_turning_angle(0.0,1.0));

        return fmin(1,curvature);
    }

    // highest speed from which the car can still brake down to v_target within dist metres.
    // simulator braking (while commanding v_target): dv/dt = -A_b * (MAX_VELOCITY - v_target) / (v + 1)
    // => dist = (F(v0) - F(v_target)) / (A_b * (MAX_VELOCITY - v_target)),  F(v) = v^3/3 + v^2/2
    static double max_entry_speed(double v_target, double dist){
        const auto F = [](double v){ return v * v * v / 3.0 + v * v / 2.0; };
        const double budget = F(v_target) + dist * BRAKE_CONSTANT * (MAX_VELOCITY - v_target);
        if (F(MAX_VELOCITY) <= budget) return MAX_VELOCITY;

        // F is monotonic for v >= 0, so bisect for F(v0) = budget
        double lo = v_target, hi = MAX_VELOCITY;
        for (int i = 0; i < 40; i++) {
            const double mid = 0.5 * (lo + hi);
            if (F(mid) < budget) lo = mid; else hi = mid;
        }
        return lo;
    }

    // calculates the speed based on a speed curve -> the curve is pulled from https://www.desmos.com/calculator/ 
    double get_speed(const double curvature) const{

        // speed gain equation : exponential
        const auto x =  this->exp_a_ * (pow(this->exp_b_,curvature));
        //const auto x = -2.5 * curvature + 1;

        auto y = fmin(this->max_speed_gain_  * x, this->max_speed_gain_);
        double speed = fmax(y,0.0) + this->base_speed_; 

        //RCLCPP_INFO(this->get_logger(), "max_err %f", max_err);

        return speed;
    }


    void stateCallback(const fsbrt_ros2_2026::msg::VehicleState::SharedPtr msg) {

        std::vector<std::pair<double, double>> horizon;
        for (const auto& point : msg->horizon.points) {
            horizon.push_back(std::make_pair(point.x, point.y));
        }
        double current_velocity = msg->current_velocity;
        double current_theta = msg->current_theta;
        geometry_msgs::msg::Point current_position = msg->current_position;
        const auto curr_pos_pair = std::make_pair(current_position.x, current_position.y);
        // ----------------------------------------------------------
        // -YOURRCLCPP_INFO CODE START------------------------------------------
        // ----------------------------------------------------------
        // TODO: Implement your logic for assigning velocity using the data from subscribers

                            
                
        // car position followed by the horizon
        std::vector<std::pair<double, double>> path{curr_pos_pair};
        path.insert(path.end(), horizon.begin(), horizon.end());

        // braking look-ahead: every spline window along the horizon gets a corner speed,
        // the car must be slow enough now to brake down to each of them in time
        double v_allowed = MAX_VELOCITY;
        double v_brake_target = MAX_VELOCITY;   // corner speed of the window that limits v_allowed
        double dist = 0.0;                      // path distance from the car to the window start
        const double curvature = curvature_calculation(path, 0);
        for (std::size_t k = 0; k + DEGREE <= path.size(); k++) {
            if (k > 0) {
                dist += std::hypot(path[k].first - path[k-1].first, path[k].second - path[k-1].second);
            }
            const double v_corner = get_speed(k == 0 ? curvature : curvature_calculation(path, k));
            const double v_entry = max_entry_speed(v_corner, this->brake_margin_ * dist);
            if (v_entry < v_allowed) {
                v_allowed = v_entry;
                v_brake_target = v_corner;
            }
        }

        //curvature_log << curr_pos_pair.first <<"," << curr_pos_pair.second << "," << curvature << "\n";
        //velocity_log << curr_pos_pair.first <<"," << curr_pos_pair.second << "," << current_velocity << "\n";

        // too fast for something ahead -> command that corner speed, which brakes as hard as
        // max_entry_speed assumes; otherwise go for the allowed speed
        auto desired_velocity = current_velocity > v_allowed ? v_brake_target : v_allowed;

        const auto& next_point = horizon[0];
        const double angle = std::atan2(next_point.second - curr_pos_pair.second,
                                            next_point.first  - curr_pos_pair.first);
        const double diff_angle = std::remainder(angle - current_theta, 2.0 * M_PI);

        const auto now = this->now();
        // arm the slow-down only on the frame the heading error first exceeds 90 deg,
        // so a long turnaround doesn't keep pushing the timer forward
        const bool heading_lost = std::abs(diff_angle) > M_PI / 2.0;
        if (heading_lost && !heading_lost_prev_) {
            RCLCPP_WARN(this->get_logger(),
                "Heading error %.2f rad > 90 deg, slowing down to base_speed for %.2f s", diff_angle, recovery_time_);
            slow_until_ = now + rclcpp::Duration::from_seconds(recovery_time_);
        }
        heading_lost_prev_ = heading_lost;
        if (now < slow_until_) {
            desired_velocity = std::min(desired_velocity, this->base_speed_);
        }



        // ----------------------------------------------------------
        // -YOUR CODE END------------------------------------------
        // ----------------------------------------------------------
        if(desired_velocity>MAX_VELOCITY) desired_velocity=MAX_VELOCITY;

        RCLCPP_INFO(this->get_logger(), "desired velocity %f", desired_velocity);
        RCLCPP_INFO(this->get_logger(), "current velocity %f", current_velocity);


        std_msgs::msg::Float64 desired_velocity_msg;
        desired_velocity_msg.data = desired_velocity;
        desired_velocity_pub_->publish(desired_velocity_msg);
    }

    rclcpp::Subscription<fsbrt_ros2_2026::msg::VehicleState>::SharedPtr state_sub_;
    rclcpp::Publisher<std_msgs::msg::Float64>::SharedPtr desired_velocity_pub_;



    double max_speed_gain_{0.0};
    double base_speed_{0.0};
    double exp_a_{0.0};
    double exp_b_{0.0};
    double recovery_time_{0.0};
    double brake_margin_{0.0};


    std::ofstream curvature_log;
    std::ofstream velocity_log;
    rclcpp::Time slow_until_{0, 0, RCL_ROS_TIME};
    bool heading_lost_prev_{false};

};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<VelocityLogic>();
    RCLCPP_INFO(node->get_logger(), "Velocity Logic node ready.");
    rclcpp::spin(node);
    rclcpp::shutdown();
    

    return 0;
}

