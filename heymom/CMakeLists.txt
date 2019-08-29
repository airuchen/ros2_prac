cmake_minimum_required(VERSION 3.5)
project(heymom)

# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)

# if(BUILD_TESTING)
#   find_package(ament_lint_auto REQUIRED)
#   # the following line skips the linter which checks for copyrights
#   # uncomment the line when a copyright and license is not present in all source files
#   #set(ament_cmake_copyright_FOUND TRUE)
#   # the following line skips cpplint (only works in a git repo)
#   # uncomment the line when this package is not in a git repo
#   #set(ament_cmake_cpplint_FOUND TRUE)
#   ament_lint_auto_find_test_dependencies()
# endif()

add_executable(qos_pub src/topic/qos_pub.cpp)
ament_target_dependencies(qos_pub rclcpp std_msgs)

add_executable(my_sub src/topic/my_sub.cpp)
ament_target_dependencies(my_sub rclcpp std_msgs)

add_executable(pub_lamda src/topic/pub_lamda.cpp)
ament_target_dependencies(pub_lamda rclcpp std_msgs)

add_executable(qos_sub src/topic/qos_sub.cpp)
ament_target_dependencies(qos_sub rclcpp std_msgs)

add_executable(reuse_timer src/topic/reuse_timer.cpp)
ament_target_dependencies(reuse_timer rclcpp std_msgs)

install(TARGETS
	qos_pub
	my_sub
	pub_lamda
	qos_sub
	reuse_timer
	DESTINATION lib/${PROJECT_NAME}
)

ament_package()
