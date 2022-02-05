#include <Arduino.h>
#include <SPI.h>
#include "printf.h"
#include "RF24.h"
#include "Reciver.hpp"
#include "ReciverData.hpp"
//#include "Racket.hpp"
#include "ResponsiveAnalogRead.h"
#include <EasyTransfer.h>

/*
██████╗ ███████╗██████╗ ██╗  ██╗
██╔══██╗██╔════╝╚════██╗██║  ██║
██████╔╝█████╗   █████╔╝███████║
██╔══██╗██╔══╝  ██╔═══╝ ╚════██║
██║  ██║██║     ███████╗     ██║
╚═╝  ╚═╝╚═╝     ╚══════╝     ╚═╝
*/
RF24 radio(21, 20); //CE pin, CSN pin
const uint64_t ADRESS{0xF0F0F0F0D2LL};
const byte CHANNEL{121};
ReciverData lr_rf24SensorData;
Reciver rr_reciver(radio, ADRESS, CHANNEL, lr_rf24SensorData);
/*
███████╗████████╗
██╔════╝╚══██╔══╝
█████╗     ██║   
██╔══╝     ██║   
███████╗   ██║   
╚══════╝   ╚═╝   
 */
EasyTransfer ET;

struct SEND_DATA_STRUCTURE
{
  //put your variable definitions here for the data you want to send
  //THIS MUST BE EXACTLY THE SAME ON THE OTHER ARDUINO
  int16_t pz;
};
SEND_DATA_STRUCTURE mydata;
void blink();

void setup()
{
  Serial.begin(9600);
 
  // while (!Serial )
  // {
  // }

  Serial8.begin(9600); // Open Serial8 for EaesyTransfer

  ET.begin(details(mydata), &Serial8);
  rr_reciver.setup();
  pinMode(24,OUTPUT);

}

void loop()
{
 
    blink();
    rr_reciver.loop();
    //ET
    mydata.pz = lr_rf24SensorData.pz;
    ET.sendData();
   
}

void blink()
{
  static elapsedMillis ms_blink;
  if (ms_blink > 1000)
  {
    static boolean toggle = true;
    toggle = !toggle;
    digitalWrite(24, toggle);

    ms_blink = 0;
  }
}