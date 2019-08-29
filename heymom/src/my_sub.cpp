#include <iostream>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

class MySub : public rclcpp::Node
{
public:
	MySub()
	: Node("my_sub")
	{
		auto callback = [this](const std_msgs::msg::String::SharedPtr msg) -> void {
			RCLCPP_INFO(this->get_logger(), "I heard: [%s]", msg->data.c_str());
		};
		sub_ = this->create_subscription<std_msgs::msg::String>("topic", callback);
	}
private:
	rclcpp::Subscription<std_msgs::msg::String>::SharedPtr sub_;
};

int main(int argc, char * argv[]) {
	rclcpp::init(argc, argv);
	auto node = std::make_shared<MySub>();
	rclcpp::spin(node);
	rclcpp::shutdown();
	return 0;
}
