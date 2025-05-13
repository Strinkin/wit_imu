cmake_minimum_required(VERSION 3.10)
project(wit_linux_c)

message("\n")
message(" ------- WIT_LINUX_C CMakeList.txt START -------")

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(wit_sdk)

# pack as a library
option(PACK_AS_LIBRARY "Pack as a library" ON)
if(PACK_AS_LIBRARY)
    message("WitImu class Packing as a library")
    set(CMAKE_POSITION_INDEPENDENT_CODE ON) # for shared library
    set(LIB_SRCS 
        src/WitImu.cpp
        src/LocalTime.cpp
    )
    add_library(wit_imu SHARED ${LIB_SRCS})
    target_include_directories(wit_imu PUBLIC ${PROJECT_SOURCE_DIR}/include)
    target_link_libraries(wit_imu PUBLIC wit_sdk)
endif()

# build example if enabled
option(BUILD_EXAMPLE "Build example executable" OFF)
if(BUILD_EXAMPLE)
    message("Building Wit example")
    set(EXAMPLE_SRCS 
        example.cpp
        src/WitImu.cpp
        src/LocalTime.cpp
    )

    add_executable(example ${EXAMPLE_SRCS})
    target_include_directories(example PRIVATE ${PROJECT_SOURCE_DIR}/include)

    target_link_libraries(example PRIVATE wit_sdk)
endif()

# build test if enabled
option(BUILD_TEST "Build wit test executable" OFF)
if(BUILD_TEST)
    message("Building test")
    set(TEST_SRCS
        test.cpp
        src/LocalTime.cpp
    )
    add_executable(test ${TEST_SRCS})
    target_link_libraries(test PRIVATE wit_sdk)
endif()

message(" ------- WIT_LINUX_C CMakeList.txt END -------")
message("\n")

