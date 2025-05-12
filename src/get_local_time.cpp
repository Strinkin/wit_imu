/*
 * @Author: strinkin strinkin@qq.com
 * @Date: 2025-05-12 
 */
#include "../include/get_local_time.h"

#include <iostream>
#include <chrono>
#include <iomanip>
#include <ctime>
#include <iostream>
#include <chrono>
#include <iomanip>
#include <ctime>

void printCurrentSystemTime() {
    // 获取当前时间点
    auto now = std::chrono::system_clock::now();
    // 转换为时间戳
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    // 转换为本地时间
    std::tm* now_tm = std::localtime(&now_c);

    // 获取毫秒部分
    auto now_ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;

    // 打印当前时间
    std::cout << "sys time: "
              << std::put_time(now_tm, "%Y-%m-%d %H:%M:%S") << ":" << std::setfill('0') << std::setw(3) << now_ms.count()
              << std::endl;
}
