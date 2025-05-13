/*
 * @Author: Strinkin strinkin@qq.com
 * @Date: 2025-05-13 
 */
#include "WitImu.hpp"

int main(int argc, char *argv[]) {
    WitImu wit_imu("/dev/wit_imu_IWT603T");
    wit_imu.run();

    return 0;
}
