cmake_minimum_required(VERSION 3.10)
project(wit_linux_c)

message("\n")
message(" ------- WIT_LINUX_C CMakeList.txt START -------")

set(CMAKE_CXX_STANDARD 11)

# build example if enabled
option(BUILD_EXAMPLE "Build example executable" ON)
if(BUILD_EXAMPLE)
    set(EXAMPLE_SRCS 
        example.cpp
        src/WitImu.cpp
        src/LocalTime.cpp
    )
    add_subdirectory(wit_sdk)

    add_executable(example ${EXAMPLE_SRCS})
    target_include_directories(example PRIVATE ${CMAKE_SOURCE_DIR}/include)

    target_link_libraries(example PRIVATE wit_sdk)
endif()

# build test if enabled
option(BUILD_TEST "Build test executable" OFF)
if(BUILD_TEST)
    set(TEST_SRCS
        test.cpp
        src/LocalTime.cpp
    )
    add_executable(test ${TEST_SRCS})
    add_subdirectory(wit_sdk)
    target_link_libraries(test PRIVATE wit_sdk)
endif()

message(" ------- WIT_LINUX_C CMakeList.txt END -------")
message("\n")

