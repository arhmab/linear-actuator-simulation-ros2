#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float64_multi_array.hpp"
#include "sensor_msgs/msg/joint_state.hpp"

using namespace std::chrono_literals;

enum class ActuatorState
{
    EXTEND,
    //RETRACT,
    IDLE
};

class ActuatorControl : public rclcpp::Node
{
public:
  ActuatorControl() : Node("actuator_control"), current_state(ActuatorState::EXTEND)
  {
    RCLCPP_INFO(get_logger(), "Actuator Control Node started");
    
    cmd_pub_ = create_publisher<std_msgs::msg::Float64MultiArray>(
        "/actuator_position_controller/commands", 10);

    timer_ = create_wall_timer(500ms, std::bind(&ActuatorControl::sendCmd, this));

  }

private:
    rclcpp::Publisher<sensor_msgs::msg::JointState>::SharedPtr cmd_pub_;
    rclcpp::TimerBase::SharedPtr timer_;

    ActuatorState current_state;
    //const auto EXTENDED_POSE = 0.25;
    //const auto RETRACTED_POSE = 0.0;

    void sendCmd(){
        sensor_msgs::msg::JointState cmd;

        switch(current_state){
            case ActuatorState::EXTEND:
                RCLCPP_INFO(get_logger(), "Lid Opening");
                cmd.name = ["actuator_extension_joint"];
                cmd.position = [0.25];
                cmd_pub_->publish(cmd);

                current_state = ActuatorState::IDLE;
                break;
            // case ActuatorState::RETRACT:
            //     RCLCPP_INFO(get_logger(), "Lid Closing");
            //     cmd.data = {RETRACTED_POSE};
            //     cmd_pub_->publish(cmd);

            //     current_state = ActuatorState::IDLE;
            //     break;
            case ActuatorState::IDLE:
                RCLCPP_INFO(get_logger(), "Lid Idle");
                timer_->cancel();
                break;
        }
    }

};

int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<ActuatorControl>();
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}