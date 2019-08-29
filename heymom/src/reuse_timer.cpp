#include <chrono>
#include <cstdio>
#include <memory>

#include "rclcpp/rclcpp.hpp"

using namespace std::chrono_literals;

class ReuseTimerNode : public rclcpp::Node
{
public:
	ReuseTimerNode() : Node("reuse_timer")
	{
		one_off_timer = this->create_wall_timer(1s, 
				[this](){
				RCLCPP_INFO(this->get_logger(), "in one_off_timer callback");
				this->one_off_timer->cancel();
				});
		one_off_timer->cancel();

		periodic_timer = this->create_wall_timer(2s,
				[this](){
				RCLCPP_INFO(this->get_logger(), "in periodic_timer callback");
				if (this->count++ %3 == 0) {
					RCLCPP_INFO(this->get_logger(), "resetting one off timer");
					this->one_off_timer->reset();
				} else {
					RCLCPP_INFO(this->get_logger(), "not resetting one off timer");
				}
				});

	}
private:
	rclcpp::TimerBase::SharedPtr periodic_timer;
	rclcpp::TimerBase::SharedPtr one_off_timer;
	size_t count;
};

int main(int argc, char* argv[])
{
	rclcpp::init(argc, argv);
	rclcpp::spin(std::make_shared<ReuseTimerNode>());
	rclcpp::shutdown();
	return 0;
}
