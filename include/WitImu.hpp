/*
 * @Author: Strinkin strinkin@qq.com
 * @Date: 2025-05-12 20:34:48
 */
#ifndef __WitImu_HPP__
#define __WitImu_HPP__

#include "serial.h"
#include "wit_c_sdk.h"
#include "REG.h"
#include <stdint.h>

#include <string>
#include <cassert>
#include "LocalTime.hpp"

#define ACC_UPDATE 0x01
#define GYRO_UPDATE 0x02
#define ANGLE_UPDATE 0x04
#define TIME_UPDATE 0x08
// #define MAG_UPDATE 0x08
#define READ_UPDATE 0x80

class WitImu {
public:
    WitImu();
    WitImu(const char* port_name = nullptr, uint32_t baudrate = 0) : m_port_name(port_name), m_baudrate(baudrate) 
    {
		assert(port_name != nullptr && "[WitImu] port_name is nullptr");
        if (m_baudrate == 0) AutoScanSensor(m_port_name.c_str());
        else m_fd = serial_open(m_port_name.c_str(), m_baudrate);
        assert(m_fd > 0 && "[WitImu] serial open failed");

		WitInit(WIT_PROTOCOL_NORMAL, 0x50); // 确定通信协议, 串口还是can还是i2c
		WitRegisterCallBack(SensorDataUpdata); // 注册回调函数, 让内部的一个函数指针指向传入的函数
    };
    ~WitImu()
	{
		serial_close(m_fd);
	}

	void run();
    void AutoScanSensor(const char *dev);
    static void SensorDataUpdata(uint32_t uiReg, uint32_t uiRegNum);
    static void Delayms(uint16_t ucMs);
private:
	// init
    std::string m_port_name;
    uint32_t m_baudrate;
    int m_fd;
	const int c_uiBaud[10] = {2400, 4800, 9600, 19200, 38400, 57600, 115200, 230400, 460800, 921600};
	LocalTime m_local_time;
	
	// runtime
    static volatile char s_cDataUpdate; // 数据更新标志位
	float fAcc[3], fGyro[3], fAngle[3];
};


#endif // __WitImu_HPP__