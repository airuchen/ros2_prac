#include <cinttypes>
#include <cstdio>
#include <memory>
#include <string>
#include <vector>

#include "rclcpp/rclcpp.hpp"

#include "example_interfaces/srv/add_two_ints.hpp"

class ServerNode : public rclcpp::Node
{
public:
	ServerNode() : Node("add_two_ints_server")
	{
		if(find_command_option(args, "-h")) {
			print_usage();
			rclcpp::shutdown();
		} else {
			std::string tmptopic = get_command_option(args, "-s");
			if (!tmptopic.empty()) {
				service_name = tmptopic;
			}
			execute();
		}
	}
	
	void execute()
	{
		auto handle_add_two_ints = 
			[this](std::shared_ptr<rmw_request_id_t> request_header,
					std::shared_ptr<example_interfaces::srv::AddTwoInts::Request> request,
					std::shared_ptr<example_interfaces::srv::AddTwoInts::response) -> void
			{
				(void)request_header;
				RCLCPP_INFO(this->get_logger(), "Incoming request\na: %"PRId64" b: %"PRId64, request->a, request->b);
				response->sum = request->a + request->b;
			};
		srv_ = create_service<example_interfaces::srv::AddTwoInts>(service_name_, handle_add_two_ints);
	}
private:
  	void print_usage()
  	{
  	 	printf("Usage for add_two_ints_server app:\n");
  	  	printf("add_two_ints_server [-s service_name] [-h]\n");
  	  	printf("options:\n");
  	  	printf("-h : Print this help function.\n");
  	  	printf("-s service_name : Specify the service name for server. Defaults to add_two_ints.\n");
  	}

	bool find_command_option(const std::vector<std::string> & args, const std::string & option)
	{
		return std::find(args.begin(), args.end(), option) != args.end();
	}

	std::string get_command_option(const std::vector<std::string> & args, const std::string & option)
	{
		auto it = std::find(args.begin(), args.end(), option);
		if (it != args.end() && ++it != args.end()) {
			return * it;
		}
		return std::string();
	}
	
	rclcpp::Service<example_interfaces::srv::AddTwoInts>::SharedPtr srv_;
	std::string service_name_ = "add_two_ints";
};

