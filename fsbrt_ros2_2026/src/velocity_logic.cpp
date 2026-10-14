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




static constexpr auto DEGREE = 4;
static_assert(DEGREE < 15);

constexpr auto BASE_SPEED{0.5};
constexpr auto MAX_GAIN_SPEED{9.0};

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

        this->declare_parameter("max_speed_gain", 9.0);
        this->declare_parameter("base_speed", 1.4);
        this->declare_parameter("exp_a", 0.948148);
        this->declare_parameter("exp_b", 0.00317121);
        this->declare_parameter("curve_degree", 4);

        this->max_speed_gain_ = this->get_parameter("max_speed_gain").as_double();
        this->base_speed_ = this->get_parameter("base_speed").as_double();
        this->exp_a_ = this->get_parameter("exp_a").as_double();
        this->exp_b_ = this->get_parameter("exp_b").as_double();


        RCLCPP_INFO(this->get_logger(),
        "Parameters: max_speed_gain=%.3f, base_speed=%.3f, exp_a=%.6f, exp_b=%.8f",
        max_speed_gain_, base_speed_, exp_a_, exp_b_);

        curvature_log.open("/home/nh-laptop/FSB-racing/task/fsbrt_ros2_2026/curvature.csv");
        

    }

private:


    // calculates the new speed based on the curvature of the spline
    double curvature_calculation(std::pair<double,double> car_pos, std::vector<std::pair<double,double>> horizon) const{

        
        
        Eigen::MatrixXd matrix(DEGREE,2);

        // first element is the current car position
        matrix(0,0) = car_pos.first;
        matrix(0,1) = car_pos.second;


        for(auto i{1U}; i < DEGREE; i++){
            matrix(i,0) = horizon[i].first;
            matrix(i,1) = horizon[i].second;
        }
        nanospline::Bezier<double, 2, DEGREE - 1> curve;
        curve.set_control_points(matrix);
        
        auto curvature = abs(curve.get_turning_angle(0.0,1.0));
        std::cout << "matrix : \n" << matrix << std::endl;
        std::cout << "spline curvature norm" <<  curvature << std::endl;; 



        return fmin(1,curvature);
        

    }

    // calculates the speed based on a speed curve -> the curve is pulled from https://www.desmos.com/calculator/oopmzrndtk 
    double get_speed(const double curvature) const{

        // speed gain equation
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

                            
                
        const auto curvature = curvature_calculation(curr_pos_pair,horizon);
        // curvature_log << count << "," << curvature << std::endl;
        // count++;
        auto desired_velocity = get_speed(curvature);

        const auto& next_point = horizon[0];
        const double angle = std::atan2(next_point.second - curr_pos_pair.second,
                                            next_point.first  - curr_pos_pair.first);
        const double diff_angle = std::remainder(angle - current_theta, 2.0 * M_PI);

            const auto now = this->now();
            if (std::abs(diff_angle) > M_PI / 2.0) {
                RCLCPP_WARN_THROTTLE(this->get_logger(), *this->get_clock(), 1000,
                    "Heading error %.2f rad > 90 deg, slowing down to base_speed", diff_angle);
                slow_until_ = now + rclcpp::Duration::from_seconds(2.5);
            }
            if (now < slow_until_) {
                desired_velocity = std::min(desired_velocity, this->base_speed_);
            }



        // ----------------------------------------------------------
        // -YOUR CODE END------------------------------------------
        // ----------------------------------------------------------
        if(desired_velocity>MAX_VELOCITY) desired_velocity=MAX_VELOCITY;

        RCLCPP_INFO(this->get_logger(), "desired speed %f", desired_velocity);


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


    std::ofstream curvature_log;
    uint64_t count{0};
    rclcpp::Time slow_until_{0, 0, RCL_ROS_TIME};

};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<VelocityLogic>();
    RCLCPP_INFO(node->get_logger(), "Velocity Logic node ready.");
    rclcpp::spin(node);
    rclcpp::shutdown();
    

    return 0;
}

