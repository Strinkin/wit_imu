/*
 * @Author: Strinkin strinkin@qq.com
 * @Date: 2025-05-12 22:29:31
 */
#include "include/WitImu.hpp"

int main() {
    WitImu wit_imu("/dev/wit_imu_IWT603T", 921600);
    wit_imu.run();
}