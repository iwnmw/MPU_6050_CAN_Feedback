#include "imuDataSender.h"
#include <Arduino.h>



// imuDataSender class implementation

imuDataSender::imuDataSender()
    : ax(0.0f), ay(0.0f), az(0.0f), roll(0.0f), pitch(0.0f), yaw(0.0f) {
    // Constructor initializes IMU data values to zero
}


void imuDataSender::update() {
    // Here you would typically read from the IMU sensor and update ax, ay, az, roll, pitch, yaw
    // For example:
    // ax = mpu.getAccX();
    // ay = mpu.getAccY();
    // az = mpu.getAccZ();
    // roll = mpu.getAngleX();
    // pitch = mpu.getAngleY();
    // yaw = mpu.getAngleZ();

    sendData(); // Call the function to send the updated IMU data
}