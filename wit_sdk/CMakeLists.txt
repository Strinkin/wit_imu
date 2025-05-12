cmake_minimum_required(VERSION 3.10)
project(wit_sdk)

message("\n")
message(" ------- WIT_SDK CMakeList.txt START -------")

# sources
file(GLOB_RECURSE SDK_SRCS ${PROJECT_SOURCE_DIR}/src/*.c)
# set(SDK_SRCS 
#     ${PROJECT_SOURCE_DIR}/src/wit_c_sdk.c
#     ${PROJECT_SOURCE_DIR}/src/serial.c
# )
message("wit_sdk source dir: ${PROJECT_SOURCE_DIR}")
message("find wit_sdk source files: ${SDK_SRCS}")
add_library(wit_sdk SHARED ${SDK_SRCS})

#headers
file(GLOB_RECURSE SDK_HEADERS ${PROJECT_SOURCE_DIR}/include/*.h)
message("find wit_sdk header files: ${SDK_HEADERS}")
target_include_directories(wit_sdk PUBLIC ${PROJECT_SOURCE_DIR}/include)

message(" -------- WIT_SDK CMakeList.txt END --------")
message("\n")


