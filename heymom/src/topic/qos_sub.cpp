#include <cstdio>
#include <memory>

#include "rclcpp/rclcpp.hpp"
// #include "rclcpp_components/register_node_macro.hpp"
#include "std_msgs/msg/string.hpp"

class BestListener : public rclcpp::Node
{
public:
	BestListener()
	: Node("listener")
	{
		auto callback = 
			[this](std_msgs::msg::String::SharedPtr msg) -> void
			{
				RCLCPP_INFO(this->get_logger(), "I heard: [%s]", msg->data.c_str());
			};

		rclcpp::QoS qos(rclcpp::KeepLast(7));
		qos
			.reliable()
			.transient_local();
		sub_ = this->create_subscription<std_msgs::msg::String>("topic", qos, callback);
	}

private:
	rclcpp::Subscription<std_msgs::msg::String>::SharedPtr sub_;
};

int main(int argc, char* argv[])
{
	rclcpp::init(argc, argv);
	rclcpp::spin(std::make_shared<BestListener>());
	rclcpp::shutdown();
	return 0;
}


// RCLCPP_COMPONENTS_REGISTER_NODE(demo_nodes_cpp::ListenerBestEffort)
