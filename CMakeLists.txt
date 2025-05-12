cmake_minimum_required(VERSION 3.10)
project(wit_linux_c)

message("\n")
message(" ------- WIT_LINUX_C CMakeList.txt START -------")

set(CMAKE_CXX_STANDARD 11)

set(SRCS 
    main.cpp
)
include_directories(./wit_sdk/include)
add_executable(${PROJECT_NAME} ${SRCS})

add_subdirectory(wit_sdk)
target_link_libraries(${PROJECT_NAME} PUBLIC wit_sdk)

message(" ------- WIT_LINUX_C CMakeList.txt END -------")
message("\n")

