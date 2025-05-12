/*
 * @Author: strinkin strinkin@qq.com
 * @Date: 2025-05-12
 */
#ifndef __LOCAL_TIME_HPP__
#define __LOCAL_TIME_HPP__

#include <chrono>
#include <ctime>
#include <array>
#include <iomanip>
#include <iostream>

class LocalTime {
public:
    LocalTime();
    void update();
    
    // 获取时间分量
    inline int getYear() const;
    inline int getMonth() const;
    inline int getDay() const;
    inline int getHour() const;
    inline int getMinute() const;
    inline int getSecond() const;
    inline int getMillisecond() const;

    // 数据接口
    void fillArray(int* local_time) const;
    void print() const;

private:
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
    int millisecond;
};

#endif // __LOCAL_TIME_HPP__
