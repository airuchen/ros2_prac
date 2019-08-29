#include <chrono>
#include <iostream>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/srv/add_two_ints.hpp"

using namespace std::chrono_literals;

void print_usage()
{
	printf("Usage for add_two_ints_client app:\n");
	printf("add_two_ints_client [9t topic_name] [-h]\n");
	printf("options:\n");
	printf("-h : Print this help function. \n");
	printf("-s service_nam:e : Specify the service name for this client. Defaults to add_two_ints.\n");
}

example_interfaces::srv::AddTwoInts::Response::SharedPtr sned_request(
		rclcpp::Node::SharedPtr node,
		rclcpp::Client<example_interfaces::srv::AddTwoInts>::SharedPtr client,
		example_interfaces::srv::AddTwoInts::Request::SharedPtr request)
{
	auto result = client->async_send_request(request);

	if (rclcpp::spin_until_future_complete(node, result) == 
			rclcpp::executor::FutureReturnCode::SUCCESS)
	{
		return result.get();
	} else {
		return NULL;
	}
}

int main(int argc, char* argv[])
{
	rclcpp::init(argc, argv);
	auto node = rclcpp::Node::make_shared("add_two_ints_client");
	
	auto topic = std::string("add_two_ints");
	auto client = node->create_client<example_interfaces::srv::AddTwoInts>(topic);

	auto request = std::make_shared<example_interfaces::srv::AddTwoInts>();
	request->a = 2;
	request->b = 3;

	while(!client->wait_for_service(1s)) {
		if(rclcpp::ok()) {
			RCLCPP_ERROR(node->get_logger(), "Interrupted while waiting for the service. Exiting." );
			return 0;
		}
		RCLCPP_INFO(node->get_logger(), "service not available, waiting again...");
	}

	auto result = send_request(node, client, request);
	if (result) {
		RCLCPP_INFO(node->get_logger(), "Result of add_two_ints: %zd", result->sum);
	} else {
		RCLCPP_ERROR(node->get_logger(), "INterrupted while waiting for response. Exiting.");
	}

	rclcpp::shutdown();
	return 0;
}
}
