cmake_minimum_required(VERSION 3.10)
project(test_module)

message("\n")
message(" ------- WIT_TEST_MODULE CMakeList.txt START -------")

add_subdirectory(wit_module)

add_executable(test_module test_module.cpp)

target_link_libraries(test_module wit_imu)

message(" -------- WIT_TEST_MODULE CMakeList.txt END --------")
message("\n")

