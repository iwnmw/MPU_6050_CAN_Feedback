#pragma once // Prevent Multiple Inclusions of the Header File

class imuDataSender {
    public:
        imuDataSender();
        void update(); // This Gets Called in the Loop to Constantly Update the Controller with New Feedback

    private:
        float ax; // Accelerometer X-axis value
        float ay; // Accelerometer Y-axis value
        float az; // Accelerometer Z-axis value
        float roll; // Roll angle
        float pitch; // Pitch angle
        float yaw; // Yaw angle

        void sendData(); // Function to Send IMU Data
};