#include "MPU6050.h"

MPU6050::MPU6050(PinName sda, PinName scl) : connection(sda, scl)
{
    this->setSleepMode(false);
    this->write(0x1C, 0x18);
    this->write(0x1B, 0x18);

    char temp[6];

    for (int i = 0; i < 6; i++)
        offset[i] = 0;

    for (int i = 0; i < 1000; i++)
    {
        this->read(MPU6050_ACCEL_XOUT_H_REG, temp, 6);
        offset[0] += (int)(short)((temp[0] << 8) + temp[1]) / 2048.0 * 9.81;
        offset[1] += (int)(short)((temp[2] << 8) + temp[3]) / 2048.0 * 9.81;
        offset[2] += (int)(short)((temp[4] << 8) + temp[5]) / 2048.0 * 9.81;

        this->read(MPU6050_GYRO_XOUT_H_REG, temp, 6);
        offset[3] += (int)(short)((temp[0] << 8) + temp[1]) / 16.4;
        offset[4] += (int)(short)((temp[2] << 8) + temp[3]) / 16.4;
        offset[5] += (int)(short)((temp[4] << 8) + temp[5]) / 16.4;

        wait_ms(1);
    }

    for (int i = 0; i < 6; i++)
        offset[i] /= 1000;
}

void MPU6050::reboot()
{
    this->setSleepMode(false);
    this->write(0x1C, 0x18);
    this->write(0x1B, 0x18);
}

void MPU6050::write(char address, char data)
{
    char temp[2];
    temp[0] = address;
    temp[1] = data;

    connection.write(MPU6050_ADDRESS * 2, temp, 2);
}

char MPU6050::read(char address)
{
    char retval;
    connection.write(MPU6050_ADDRESS * 2, &address, 1, true);
    connection.read(MPU6050_ADDRESS * 2, &retval, 1);
    return retval;
}

int MPU6050::read(char address, char *data, int length)
{
    connection.write(MPU6050_ADDRESS * 2, &address, 1, true);
    return connection.read(MPU6050_ADDRESS * 2, data, length);
}

bool MPU6050::read(void)
{
    char temp[6];

    // 加速度
    if (read(MPU6050_ACCEL_XOUT_H_REG, temp, 6) != 0)
        return false;
    read(MPU6050_ACCEL_XOUT_H_REG, temp, 6);
    value[0] = (int)(short)((temp[0] << 8) + temp[1]) / 2048.0 * 9.81;
    value[1] = (int)(short)((temp[2] << 8) + temp[3]) / 2048.0 * 9.81;
    value[2] = (int)(short)((temp[4] << 8) + temp[5]) / 2048.0 * 9.81;

    // ジャイロ
    if (read(MPU6050_GYRO_XOUT_H_REG, temp, 6) != 0)
        return false;
    value[3] = (double)(short)((temp[0] << 8) + temp[1]) / 16.4;
    value[4] = (double)(short)((temp[2] << 8) + temp[3]) / 16.4;
    value[5] = (double)(short)((temp[4] << 8) + temp[5]) / 16.4;

    this->read(MPU6050_TEMP_H_REG, temp, 2);

    // 温度
    if (read(MPU6050_TEMP_H_REG, temp, 2) != 0)
        return false;
    value[6] = ((temp[0] << 8) + temp[1] + 12421.0) / 340.0;

    return true;
}

void MPU6050::setSleepMode(bool state)
{
    char temp;
    temp = this->read(MPU6050_PWR_MGMT_1_REG);
    if (state == true)
        temp |= 1 << MPU6050_SLP_BIT;
    if (state == false)
        temp &= ~(1 << MPU6050_SLP_BIT);
    this->write(MPU6050_PWR_MGMT_1_REG, temp);
}

void MPU6050::getAccelero(int option, double data[3])
{
    for (int i = 0; i < 3; i++)
        data[i] = value[i];

    if (option == MPU6050_RAW)
        return;

    for (int i = 0; i < 3; i++)
        data[i] -= offset[i];
}

void MPU6050::getGyro(int option, double data[3])
{
    for (int i = 0; i < 3; i++)
        data[i] = value[i + 3];

    if (option == MPU6050_RAW)
        return;

    for (int i = 0; i < 3; i++)
        data[i] -= offset[i + 3];
}

double MPU6050::getTemp(void)
{
    short retval;
    char data[2];
    this->read(MPU6050_TEMP_H_REG, data, 2);
    retval = (data[0] << 8) + data[1];
    return (retval + 12421.0) / 340.0;
}
