#include "I2C.h"

void initWire() {
    Wire2.begin();
}

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
 uint8_t data; // `data` will store the register data
 Wire2.beginTransmission(address);      // Initialize the Tx buffer
 Wire2.write(subAddress);	                 // Put slave register address in Tx buffer
 Wire2.endTransmission(false);             // Send the Tx buffer, but send a restart to keep connection alive
 Wire2.requestFrom(address, (uint8_t) 1);  // Read one byte from slave register address
 data = Wire2.read();                      // Fill Rx buffer with result
 return data;                             // Return data read from slave register
}


void I2Cscan()
 {
// scan for i2c devices
 byte error, address;
 int nDevices;

 Serial.println("Scanning...");

 nDevices = 0;
 for(address = 1; address < 127; address++ )
{
  // The i2c_scanner uses the return value of
   // the Write.endTransmisstion to see if
  // a device did acknowledge to the address.
  Wire2.beginTransmission(address);
  error = Wire2.endTransmission();

  if (error == 0)
  {
      Serial.print("I2C device found at address 0x");
    if (address<16)
      Serial.print("0");
    Serial.print(address,HEX);
    Serial.println("  !");

    nDevices++;
 }
  else if (error==4)
{
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
