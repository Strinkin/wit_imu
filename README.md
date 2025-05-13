# WIT IMU 的二次封装
## 本代码基于官方的linux_c示例进行开发
- 添加片上时间读取的代码
- 对sdk添加部分注释有助于理解
- 封装为一个类，并打包成库,方便链接使用
# 文件结构及介绍
```c++
├── CMakeLists.txt              // 主CMakeLists.txt
├── example.cpp                 // IMU类示例代码  
├── include                     // 头文件
│   ├── get_local_time.h
│   ├── LocalTime.hpp
│   └── WitImu.hpp              // IMU类头文件
├── src                         // 源文件
│   ├── get_local_time.cpp
│   ├── LocalTime.cpp
│   └── WitImu.cpp              // IMU类源文件
├── test.cpp                    // 测试代码,由官方示例main.c改编而来
├── test_module                 // 此项目的独立模块, 用于模拟外部调用该库
│   ├── CMakeLists.txt          // 模拟外部调用该库的CMakeLists.txt
│   ├── test_module.cpp         // 模拟外部调用该库的测试代码
│   └── wit_module              // 内含`头文件`,`源文件`,`主CMakeLists.txt`的软链接
└── wit_sdk                     // 由官方sdk改编而来,封装为库
    ├── CMakeLists.txt
    ├── include
    └── src
```

