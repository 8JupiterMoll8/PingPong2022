#include <Arduino.h>
#include <Wire.h>

int led = 24;

void setup()
{
  pinMode(led, OUTPUT);
  Wire.begin(); // join i2c bus (address optional for master)
  Wire.setSCL(19);
  Wire.setSDA(18);
}

byte x = 0;

void loop()
{
  digitalWrite(led, HIGH);    // briefly flash the LED
  Wire.beginTransmission(9);  // transmit to device #9
  Wire.write("x is ");        // sends five bytes
  Wire.write(x);              // sends one byte
  Wire.endTransmission();     // stop transmitting
  digitalWrite(led, LOW);
  delay(500);
  x++;
 
}
