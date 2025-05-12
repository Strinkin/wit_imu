#include "serial.h"
#include "wit_c_sdk.h"
#include "REG.h"
#include <stdint.h>

#include <string>
#include <chrono>

#define ACC_UPDATE 0x01
#define GYRO_UPDATE 0x02
#define ANGLE_UPDATE 0x04
#define TIME_UPDATE 0x08
// #define MAG_UPDATE 0x08
#define READ_UPDATE 0x80

static int fd, s_iCurBaud = 9600;
static volatile char s_cDataUpdate = 0;

const int c_uiBaud[] = {2400, 460800, 4800, 9600, 19200, 38400, 57600, 115200, 230400, 921600};

static void AutoScanSensor(const char *dev);
static void SensorDataUpdata(uint32_t uiReg, uint32_t uiRegNum);
static void Delayms(uint16_t ucMs);

using namespace std;
int main(int argc, char *argv[])
{

	// if(argc < 2)
	// {
	// 	printf("please input dev name\n");
	// 	return 0;
	// }

	const char* port_name = "/dev/wit_imu_IWT603T";
	fd = serial_open(port_name, 921600);
	if ((fd < 0))
	{
		printf("open %s fail\n", port_name);
		return 0;
	}
	else
		printf("open %s success\n", port_name);

	float fAcc[3], fGyro[3], fAngle[3];
	int i, ret;
	unsigned char cBuff[1];

	WitInit(WIT_PROTOCOL_NORMAL, 0x50); // 确定通信协议, 串口还是can还是i2c
	WitRegisterCallBack(SensorDataUpdata); // 注册回调函数, 让内部的一个函数指针指向传入的函数

	printf("\r\n********************** wit-motion Normal example  ************************\r\n");
	// AutoScanSensor(port_name);
	auto start_time = chrono::steady_clock::now();
	while (1)
	{
		while (serial_read_data(fd, cBuff, 1))
		{
			WitSerialDataIn(cBuff[0]);
		}
		// printf("\n");
		// Delayms(1);
		usleep(800);
		if (s_cDataUpdate)
		{
			for (i = 0; i < 3; i++)
			{
				fAcc[i] = sReg[AX + i] / 32768.0f * 16.0f;
				fGyro[i] = sReg[GX + i] / 32768.0f * 2000.0f;
				fAngle[i] = sReg[Roll + i] / 32768.0f * 180.0f;
			}

			

			char check[4] = {0, 0, 0, 0};
			if (s_cDataUpdate & ACC_UPDATE)
			{
				printf("acc:%.3f %.3f %.3f\r\n", fAcc[0], fAcc[1], fAcc[2]);
				printf("temprature:%.3f\r\n", sReg[TEMP]/100.0f);
				s_cDataUpdate &= ~ACC_UPDATE;
				check[0] = 1;
			}
			if (s_cDataUpdate & GYRO_UPDATE)
			{
				printf("gyro:%.3f %.3f %.3f\r\n", fGyro[0], fGyro[1], fGyro[2]);
				s_cDataUpdate &= ~GYRO_UPDATE;
				check[1] = 1;
			}
			if (s_cDataUpdate & ANGLE_UPDATE)
			{
				printf("angle:%.3f %.3f %.3f\r\n", fAngle[0], fAngle[1], fAngle[2]);
				s_cDataUpdate &= ~ANGLE_UPDATE;
				check[2] = 1;
			}
			if (s_cDataUpdate & TIME_UPDATE)
			{
				uint16_t Y_M = sReg[YYMM];
				uint16_t D_H = sReg[DDHH];
				uint16_t M_S = sReg[MMSS];
				uint16_t ms = sReg[MS];
				uint8_t year = (Y_M >> 8) & 0xFF;
				uint8_t month = (Y_M & 0xFF);
				uint8_t day = (D_H >> 8) & 0xFF;
				uint8_t hour = (D_H & 0xFF);
				uint8_t minute = (M_S >> 8) & 0xFF;
				uint8_t second = (M_S & 0xFF);
				printf("time:%04d-%02d-%02d %02d:%02d:%02d:%06d\r\n", year, month, day, hour, minute, second, ms);
				s_cDataUpdate &= ~TIME_UPDATE;
				check[3] = 1;
			}
			// if (s_cDataUpdate & MAG_UPDATE)
			// {
			// 	printf("mag:%d %d %d\r\n", sReg[HX], sReg[HY], sReg[HZ]);
			// 	s_cDataUpdate &= ~MAG_UPDATE;
			// 	check[3] = 1;
			// }
			if (check[0] == 1 || check[1] == 1 || check[2] == 1 || check[3] == 1)
			{
				auto end_time = chrono::steady_clock::now();
				auto duration = chrono::duration_cast<chrono::microseconds>(end_time - start_time);
				printf("duration: %ld us\r\n", duration.count());
				printf("Rate:%.2f hz\r\n", 1000.0f / (duration.count() / 1000.0f));
				start_time = end_time;
			}
		}
	}

	serial_close(fd);
	return 0;
}

static void SensorDataUpdata(uint32_t uiReg, uint32_t uiRegNum)
{
	int i;
	for (i = 0; i < uiRegNum; i++)
	{
		switch (uiReg)
		{
			//            case AX:
			//            case AY:
		case AZ:
			s_cDataUpdate |= ACC_UPDATE;
			break;
			//            case GX:
			//            case GY:
		case GZ:
			s_cDataUpdate |= GYRO_UPDATE;
			break;
			//            case HX:
			//            case HY:
		// case HZ:
		// 	s_cDataUpdate |= MAG_UPDATE;
		// 	break;
			//            case Roll:
			//            case Pitch:
		case Yaw:
			s_cDataUpdate |= ANGLE_UPDATE;
			break;
		// case YYMM:
		// case DDHH:
		// case MMSS:
		case MS:
			s_cDataUpdate |= TIME_UPDATE;
			break;
		default:
			s_cDataUpdate |= READ_UPDATE;
			break;
		}
		uiReg++;
	}
}

static void Delayms(uint16_t ucMs)
{
	usleep(ucMs * 1000); 
}

static void AutoScanSensor(const char *dev)
{
	int i, iRetry;
	unsigned char cBuff[1];

	for (i = 1; i < 10; i++)
	{
		serial_close(fd);
		s_iCurBaud = c_uiBaud[i];
		fd = serial_open(dev, c_uiBaud[i]);
		printf("try %d baud\r\n", c_uiBaud[i]);
		iRetry = 2;
		do
		{
			s_cDataUpdate = 0;
			// WitReadReg(AX, 3); // strinkin将此行代码设为注释
			Delayms(200);
			while (serial_read_data(fd, cBuff, 1))
			{
				WitSerialDataIn(cBuff[0]);
			}
			if (s_cDataUpdate != 0) // WitSerialDataIn函数检测并处理完一帧,会把s_cDataUpdate根据协议提示(加速度或角速度等)更新完成
			{
				printf("%d baud find sensor\r\n\r\n", c_uiBaud[i]);
				return;
			}
			iRetry--;
		} while (iRetry);
	}
	printf("can not find sensor\r\n");
	printf("please check your connection\r\n");
}
