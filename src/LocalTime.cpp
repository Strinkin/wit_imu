/*
 * @Author: strinkin strinkin@qq.com
 * @Date: 2025-05-13 00:05:32
 */
#include "LocalTime.hpp"

// 类外成员函数定义
LocalTime::LocalTime() { 
    update(); 
}

void LocalTime::update() {
    auto now = std::chrono::system_clock::now();
    std::time_t t = std::chrono::system_clock::to_time_t(now);
    tm* local_tm = std::localtime(&t);
    
    year = local_tm->tm_year + 1900;
    month = local_tm->tm_mon + 1;
    day = local_tm->tm_mday;
    hour = local_tm->tm_hour;
    minute = local_tm->tm_min;
    second = local_tm->tm_sec;
    
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
        now.time_since_epoch()) % 1000;
    millisecond = ms.count();
}

int LocalTime::getYear() const { return year; }
int LocalTime::getMonth() const { return month; }
int LocalTime::getDay() const { return day; }
int LocalTime::getHour() const { return hour; }
int LocalTime::getMinute() const { return minute; }
int LocalTime::getSecond() const { return second; }
int LocalTime::getMillisecond() const { return millisecond; }

void LocalTime::fillArray(int* local_time) const {
    local_time[0] = year;
    local_time[1] = month;
    local_time[2] = day;
    local_time[3] = hour;
    local_time[4] = minute;
    local_time[5] = second;
    local_time[6] = millisecond;
}

void LocalTime::print() const {
    std::cout << "sys time: " 
              << std::setfill('0') 
              << std::setw(4) << year << "-"
              << std::setw(2) << month << "-"
              << std::setw(2) << day << " "
              << std::setw(2) << hour << ":"
              << std::setw(2) << minute << ":"
              << std::setw(2) << second << ":" 
              << std::setw(3) << millisecond 
              << std::endl;
}