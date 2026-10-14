#include <cassert>
#include <rclcpp/logging.hpp>
#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/float64.hpp>
#include <geometry_msgs/msg/point.hpp>
#include <fsbrt_ros2_2026/msg/vehicle_state.hpp>
#include <cmath>
#include <vector>
#include <utility>
#include <memory>
#include <format>


#include <nanospline/Bezier.h>
#include <Eigen/Dense>

#define MAX_VELOCITY 19.5

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
    }

private:
    // matches the the waypoints onto a graph line and returns the average error
    // if error LARGE then incoming section NOT LINE, if error small then incoming section LINE-esqe
    // this outputs square error
    double linear_regression_err(std::vector<std::pair<double,double>> horizon){

        double alpha{0.0}, beta={0.0}, avg_err{0.0}, x_avg{0.0}, y_avg{0.0}, tmp1{0.0}, tmp2{0.0}, max_err{-1};

        for(auto i{0UL}; i < horizon.size(); i++)
        {
            x_avg += horizon[i].first;
            y_avg += horizon[i].second;

        }
        x_avg /= horizon.size();
        y_avg /= horizon.size();


        for(const auto &el : horizon){
            tmp1 += (el.first - x_avg) * (el.second - y_avg);
            tmp2 += (el.first - x_avg) * (el.first - x_avg);
        }

        beta = tmp1 / tmp2;
        alpha = y_avg - beta * x_avg;

        // RCLCPP_INFO(this->get_logger(), "horizon size : %lu", horizon.size());
        // RCLCPP_INFO(this->get_logger(), "alpha : %f beta : %f",alpha, beta);
        
        // eq : y = alpha +  x * beta


        // now we calculate the total error


        for(const auto &el : horizon){
            std::pair<double,double> predicted;
            predicted.first = el.first;
            predicted.second = alpha +  el.first * beta;
            auto err =  sqrt(
                (predicted.first - el.first) * (predicted.first - el.first) + 
                (predicted.second - el.second) * (predicted.second - el.second)
            );
            avg_err += err;
            if(err > max_err) max_err = err;
        }

        //return avg_err / horizon.size();
        return max_err;
    }


    double curvature(std::pair<double, double> p1, std::pair<double, double> p2, std::pair<double, double> p3){

        std::pair<double, double> u, v;
        double n, m, w_u, w_v, kapa;
        
        u.first = p1.first - p2.first;
        u.second = p1.second - p2.second;

        v.first = p3.first - p2.first;
        v.second = p3.second - p3.second;

        w_u = pow(u.first,2) + pow(u.second,2);
        w_v = pow(v.first,2) + pow(v.second,2);


        n = u.first * v.second - v.first * u.second;
        
        auto tmp1 = pow((w_u * v.first - w_v*u.first),2);
        auto tmp2 = pow((w_u * v.second - w_v*u.second),2);
        if(tmp1 + tmp2 <= 0.0 ) return 0.0;
        
        kapa = 2 * n / sqrt(tmp1 + tmp2);
        
        return kapa;

    }


    // calculates the new speed based on the curvature of the spline
    double curvature_nano_spline_speed_gain(std::pair<double,double> car_pos, std::vector<std::pair<double,double>> horizon){

        static constexpr auto degree = 4;
        
        
        Eigen::MatrixXd matrix(degree,2);
        matrix(0,0) = car_pos.first;
        matrix(0,1) = car_pos.second;
        for(auto i{1U}; i < degree; i++){
            matrix(i,0) = horizon[i].first;
            matrix(i,1) = horizon[i].second;
        }

        nanospline::Bezier<double, 2, degree - 1> curve;
        curve.set_control_points(matrix);
        
        auto curvature_normed = abs(curve.get_turning_angle(0.0,1.0));
        std::cout << "matrix : \n" << matrix << std::endl;
        std::cout << "spline curvature norm" <<  curvature_normed << std::endl;; 

        // 1.87208\cdot\left(4.34894\times10^{-7}\right)^{x}


        return abs(1.87208 * pow(4.34894 * pow(10,-7), curvature_normed));
        

    }


    void stateCallback(const fsbrt_ros2_2026::msg::VehicleState::SharedPtr msg) {

        std::vector<std::pair<double, double>> horizon;
        for (const auto& point : msg->horizon.points) {
            horizon.push_back(std::make_pair(point.x, point.y));
        }
        double current_velocity = msg->current_velocity;
        double current_theta = msg->current_theta;
        geometry_msgs::msg::Point current_position = msg->current_position;
        // ----------------------------------------------------------
        // -YOURRCLCPP_INFO CODE START------------------------------------------
        // ----------------------------------------------------------
        // TODO: Implement your logic for assigning velocity using the data from subscribers

        // const auto horizon_dbg = [&](){
        //     std::string output = ""; 
        //     for(const auto &el : horizon) 
        //         output += std::format("({}, {})", el.first, el.second);
        //     return output;
        // };
        // RCLCPP_INFO(this->get_logger(), "%s", horizon_dbg().c_str());
        //auto test = std::vector<std::pair<double,double>>(horizon.cbegin(),horizon.cbegin() + 6);
        //auto max_err = linear_regression_err(horizon);


        // auto kapa = curvature(
        //     horizon[2], 
        //     horizon[4],
        //     horizon[8]
        // );
        
        
        
        // std::vector<double> curvatures;
        // std::string curvatures_str = "";
        // for(auto i{0U}; i < horizon.size()-3; i++){
        //     auto r = curvature(horizon[i], horizon[i+1], horizon[i+2]);
        //     curvatures.push_back(
        //         r
        //     );
        //     curvatures_str += std::format(" {} ",r);
        // }
        
                
                
                
        // map 0.0 - 0.5 to 0 - 100
                
        auto speed_gain = curvature_nano_spline_speed_gain(std::make_pair(current_position.x, current_position.y),horizon);
        
        constexpr auto base_speed{.9};
        constexpr auto max_gain_speed{9.0};
        // speed gain equation
        auto curvature_speed = fmin(max_gain_speed  * speed_gain, max_gain_speed);
        double desired_velocity = fmax(curvature_speed,0.0) + base_speed; 

        //RCLCPP_INFO(this->get_logger(), "max_err %f", max_err);
        RCLCPP_INFO(this->get_logger(), "speed %f", desired_velocity);
        

        // if(max_err <=1.2) desired_velocity = 5;
        // else if(max_err > 1.2 && max_err < 1.5) desired_velocity = 2;
        // else desired_velocity = 1.2;
        

        // ----------------------------------------------------------
        // -YOUR CODE END------------------------------------------
        // ----------------------------------------------------------

        if(desired_velocity>MAX_VELOCITY) desired_velocity=MAX_VELOCITY;

        std_msgs::msg::Float64 desired_velocity_msg;
        desired_velocity_msg.data = desired_velocity;
        desired_velocity_pub_->publish(desired_velocity_msg);
    }

    rclcpp::Subscription<fsbrt_ros2_2026::msg::VehicleState>::SharedPtr state_sub_;
    rclcpp::Publisher<std_msgs::msg::Float64>::SharedPtr desired_velocity_pub_;
};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<VelocityLogic>();
    RCLCPP_INFO(node->get_logger(), "Velocity Logic node ready.");
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}

