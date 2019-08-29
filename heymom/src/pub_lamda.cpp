#include <chrono>
#include <memory>

#include "rclcpp/rclcpp.hpp"
// #include "rclcpp_components/register_node_macro.hpp"
#include "std_msgs/msg/string.hpp"

using namespace std::chrono_literals;

class PubLamda : public rclcpp::Node
{
public:
	PubLamda() 
	: Node("pub_lamda"), count_(0)
	{
		auto publish_message = 
			[this]() -> void 
			{
				msg_ = std::make_unique<std_msgs::msg::String>();
				msg_->data = "Hey Mom, I'm here!" + std::to_string(count_++);
				RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", msg_->data.c_str());
				pub_->publish(std::move(msg_));
			};

		rclcpp::QoS qos(rclcpp::KeepLast(7));

		pub_ = this->create_publisher<std_msgs::msg::String>(topic_name_, qos);

		timer_ = this->create_wall_timer(500ms, publish_message);
	}
private:
	size_t count_;
	rclcpp::Publisher<std_msgs::msg::String>::SharedPtr pub_;
	rclcpp::TimerBase::SharedPtr timer_;
	std::string topic_name_ = "chatter";
	std::unique_ptr<std_msgs::msg::String> msg_;
};

// RCLCPP_COMPONENTS_REGISTER_NODE(heymom_nodes_cpp::PubLamda)i

int main(int argc, char* argv[])
{
	rclcpp::init(argc, argv);
	rclcpp::spin(std::make_shared<PubLamda>());
	rclcpp::shutdown();
	return 0;
}
