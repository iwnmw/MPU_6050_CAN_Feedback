/* Get all possible data from MPU6050
 * Accelerometer values are given as multiple of the gravity [1g = 9.81 m/s²]
 * Gyro values are given in deg/s
 * Angles are given in degrees
 * Note that X and Y are tilt angles and not pitch/roll.
 *
 * License: MIT
 */

// Inclusions:
#include <Arduino.h>
#include "Wire.h"
#include <MPU6050_light.h>
#include <SPI.h>
#include <mcp_can.h>

// Initializing values:
// Define the SPI Chip Select Pin for MCP_CAN
const int SPI_CS_PIN = 7;

// Initialize floats to store MPU6050 data
float ax, ay, az; // Accelerometer values
float roll, pitch, yaw; // Angles
// Initialize byte objects to send over CAN bus
uint8_t axData[4], ayData[4], azData[4];
uint8_t rollData[4], pitchData[4], yawData[4];

MPU6050 mpu(Wire);

MCP_CAN CAN(SPI_CS_PIN); // Create CAN object with CS pin

unsigned long timer = 0;

void setup() {
  // Setting up CAN bus:
  bool canInitialized = false;

  // Add a short delay to ensure power stability before initializing CAN
  delay(500);

  while (!canInitialized) {
    if (CAN.begin(MCP_ANY, CAN_500KBPS, MCP_8MHZ) == CAN_OK) {
      canInitialized = true;
    } else {
      delay(500); // Wait a bit before retrying
    }
  }
  CAN.setMode(MCP_NORMAL); // Normal mode

  // Setting up I2C with the MPU6050:
  Wire.begin();
  byte status = mpu.begin();
  while(status!=0){ } // stop everything if could not connect to MPU6050
  
  // Ofsetting MPU 6050:
  delay(1000);
  mpu.calcOffsets(true,true); // gyro and accelero
}

void loop() {
  mpu.update();

  if(millis() - timer > 100){
    // Serial.print(F("TEMPERATURE: "));Serial.println(mpu.getTemp());
    // Serial.print(F("ACCELERO  X: "));Serial.print(mpu.getAccX());
    // Serial.print("\tY: ");Serial.print(mpu.getAccY());
    // Serial.print("\tZ: ");Serial.println(mpu.getAccZ());
  
    // Serial.print(F("GYRO      X: "));Serial.print(mpu.getGyroX());
    // Serial.print("\tY: ");Serial.print(mpu.getGyroY());
    // Serial.print("\tZ: ");Serial.println(mpu.getGyroZ());
  
    // Serial.print(F("ACC ANGLE X: "));Serial.print(mpu.getAccAngleX());
    // Serial.print("\tY: ");Serial.println(mpu.getAccAngleY());
    
    // Serial.print(F("ANGLE     X: "));Serial.print(mpu.getAngleX());
    // Serial.print("\tY: ");Serial.print(mpu.getAngleY());
    // Serial.print("\tZ: ");Serial.println(mpu.getAngleZ());
    // Serial.println(F("=====================================================\n"));
    timer = millis();

    // Converting float values to byte arrays for CAN transmission
    float ax = mpu.getAccX();
    float ay = mpu.getAccY();
    float az = mpu.getAccZ();
    float roll = mpu.getAngleX();
    float pitch = mpu.getAngleY();
    float yaw = mpu.getAngleZ();

    memcpy(axData, &ax, sizeof(float));
    memcpy(ayData, &ay, sizeof(float));
    memcpy(azData, &az, sizeof(float));
    memcpy(rollData, &roll, sizeof(float));
    memcpy(pitchData, &pitch, sizeof(float));
    memcpy(yawData, &yaw, sizeof(float));


    // Sending data over CAN bus
    CAN.sendMsgBuf(0x120, 0, 4, axData);
    CAN.sendMsgBuf(0x121, 0, 4, ayData);
    CAN.sendMsgBuf(0x122, 0, 4, azData);
    CAN.sendMsgBuf(0x123, 0, 4, rollData);
    CAN.sendMsgBuf(0x124, 0, 4, pitchData);
    CAN.sendMsgBuf(0x125, 0, 4, yawData);
  }
}