#ifndef MPU6050_H
#define MPU6050_H
#include "mbed.h"
#ifndef MPU6050_ADDRESS
#define MPU6050_ADDRESS 0x68
#endif

#define MPU6050_ACCEL_XOUT_H_REG 0x3B
#define MPU6050_TEMP_H_REG 0x41
#define MPU6050_GYRO_XOUT_H_REG 0x43
#define MPU6050_PWR_MGMT_1_REG 0x6B
#define MPU6050_SLP_BIT 6

#define MPU6050_RAW 0
#define MPU6050_CORRECT 1

class MPU6050
{
  public:
    MPU6050(PinName sda, PinName scl);
    void reboot();
    void getAccelero(int option, double data[3]);
    void getGyro(int option, double data[3]);
    double getTemp(void);
    void setSleepMode(bool state);
    void write(char address, char data);
    bool read();

  private:
    I2C connection;
    double value[7];
    long double offset[6];
    char read(char adress);
    int read(char adress, char *data, int length);
};

#endif
