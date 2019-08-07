#include "I2C.h"

void I2Cread(uint8_t address, uint8_t registerAddress, uint8_t nBytes, uint8_t *data) {
  Wire2.beginTransmission(address);
  Wire2.write(registerAddress);
  Wire2.endTransmission();
  Wire2.requestFrom(address, nBytes);
  uint8_t index = 0;
  while (Wire2.available()) {
    data[index] = Wire2.read();
    index++;
  }
}

void I2CwriteByte(uint8_t address, uint8_t registerAddress, uint8_t data) {
  Wire2.beginTransmission(address);
  Wire2.write(registerAddress);
  Wire2.write(data);
  Wire2.endTransmission();
}

uint8_t I2Cread(uint8_t address, uint8_t subAddress) {
  uint8_t data;
  Wire2.beginTransmission(address);
  Wire2.write(subAddress);
  Wire2.endTransmission(false);
  Wire2.requestFrom(address, (uint8_t) 1);
  data = Wire2.read();
  return data;
}

void I2Cscan() {
  byte error, address;
  int nDevices;
  Serial.println("Scanning...");
  nDevices = 0;
  for(address = 1; address < 127; address++ ) {
    Wire2.beginTransmission(address);
    error = Wire2.endTransmission();
    if (error == 0) {
      Serial.print("I2C device found at address 0x");
      if (address<16)
        Serial.print("0");
      Serial.print(address,HEX);
      Serial.println("  !");
      nDevices++;
    } else if (error==4) {
      Serial.print("Unknow error at address 0x");
      if (address<16)
        Serial.print("0");
      Serial.println(address,HEX);
    }
  }
  if (nDevices == 0)
    Serial.println("No I2C devices found\n");
  else
    Serial.println("done\n");
}
