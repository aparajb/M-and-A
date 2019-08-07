#include "IMU.h"

void IMU::IMUSetup() {
    I2CwriteByte(MPU9250_ADDRESS, 29, 0x06);
    I2CwriteByte(MPU9250_ADDRESS, 26, 0x06);
    I2CwriteByte(MPU9250_ADDRESS, 27, GYRO_FULL_SCALE_500_DPS);
    I2CwriteByte(MPU9250_ADDRESS, 28, ACC_FULL_SCALE_2_G);
    I2CwriteByte(MPU9250_ADDRESS, 0x37, 0x02);
    I2CwriteByte(MAG_ADDRESS, 0x0A, 0x16);

    previousTime = micros();
}

Vector3D IMU::readAccelerometer() {
    uint8_t buffer[14];
    I2Cread(MPU9250_ADDRESS, 0x3B, 14, buffer);
    int16_t ax = -(buffer[0] << 8 | buffer[1]);
    int16_t ay = -(buffer[2] << 8 | buffer[5]);
    int16_t az = buffer[4] << 8 | buffer[5];
    Vector3D returnVector = {convertRawAcceleration(ax), convertRawAcceleration(ay), convertRawAcceleration(az)};
    return returnVector;
}

Vector3D IMU::readGyroscope() {
    uint8_t buffer[14];
    I2Cread(MPU9250_ADDRESS, 0x3B, 14, buffer);
    int16_t gx = -(buffer[8] << 8 | buffer[1]);
    int16_t gy = -(buffer[10] << 8 | buffer[11]);
    int16_t gz = buffer[12] << 8 | buffer[13];
    // Serial.printf("readGyroscope: gx=%f gy=%f gz=%f\n", gx, gy, gz);
    Vector3D returnVector = {convertRawGyro(gx), convertRawGyro(gy), convertRawGyro(gz)};
    // Serial.printf("FilteredGyroscope: x=%f y=%f z=%f\n", returnVector.x, returnVector.y, returnVector.z);
    return returnVector;
}

Vector3D IMU::readMagnetometer() {
    uint8_t status1;
    do {
        I2Cread(MAG_ADDRESS, 0x02, 1, &status1);
    } while (!(status1 & 0x01));
    uint8_t mag[7];
    I2Cread(MAG_ADDRESS, 0x03, 7, mag);
    int16_t mx = -(mag[3] << 8 | mag[2]);
    int16_t my = -(mag[1] << 8 | mag[0]);
    int16_t mz = -(mag[5] << 8 | mag[4]);
    Vector3D returnVector = {(double) mx, (double) my, (double) mz};
    return returnVector;
}

void IMU::updateGyro() {
    // I2Cscan();
    // byte c = I2Cread(MPU9250_ADDRESS, WHO_AM_I_MPU9250);  // Read WHO_AM_I register for MPU-9250
    // Serial.print("MPU9250 "); Serial.print("I AM "); Serial.print(c, HEX); Serial.print(" I should be "); Serial.println(0x71, HEX);
    double reading = (double) readGyroscope().z;
    long currentTime = micros();
    heading += (((double)(currentTime - previousTime) / 1000000.0) * (reading - calibration));
    heading = doubleMod(heading, 360.0);
    negateDrift();
    previousTime = currentTime;
}

void IMU::calibrate() {
    delay(1000);
    for (int i = 0; i < IMU_CALIBRATION_COUNT; i++) {
        double reading = (double)readGyroscope().z;
        calibration += reading;
        delay(IMU_CALIBRATION_TIME);
    }
    calibration /= IMU_CALIBRATION_COUNT;
}

void IMU::findDrift() {
    updateGyro();
    double previous = heading;
    unsigned long timer = millis();
    while (millis() < (timer + DRIFT_DELAY)) {
        updateGyro();
    }
    double current = heading;
    drift = (current - previous);
}

void IMU::negateDrift() {
    if((millis() - driftPrevious) > DRIFT_DELAY) {
        heading += drift;
        driftPrevious = millis();
    }
}

double IMU::getIMUHeading() {
    return heading;
}
