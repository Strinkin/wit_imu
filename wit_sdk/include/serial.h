/*
 * @Author: Strinkin 2638578339@qq.com
 * @Date: 2025-05-04 16:48:06
 * @LastEditors: Strinkin 2638578339@qq.com
 * @LastEditTime: 2025-05-12 16:28:00
 * @FilePath: /normal/wit_sdk/include/serial.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */

#ifndef SERIAL_H
#define SERIAL_H

#include <linux/types.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <string.h>
#include <linux/rtc.h>
#include <termios.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

void serial_close(int fd);

int serial_open(const char* dev, unsigned int baud);

int serial_read_data(int fd, unsigned char *val, int len);

int serial_write_data(int fd, unsigned char *val, int len);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // SERIAL_H
