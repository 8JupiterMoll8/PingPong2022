#include <Arduino.h>
#include <WS2812Serial.h>
#define USE_WS2812SERIAL
#include <FastLED.h>
#include <SPI.h>
#include "printf.h"
#include "RF24.h"
#include "PeaKDetector.hpp"
//#include "Racket.hpp"
#include "Counter.hpp"
#include "I_InputSensorBhv.hpp"
#include "InputSensorRaw.hpp"
#include "InputSensorSmooth.hpp"
#include "Piezo.hpp"
#include "Birnen.hpp"
#include <EasyTransfer.h>
#include "Swing.hpp"
#include "SensorFusion.h"
#include "Mahony.hpp"
#include "Pressure.hpp"
#include "Speed.hpp"
#include "Racket.hpp" 
#include "Reciver.hpp"
#include "ReciverData.hpp"
//#include "Racket.hpp"
#include "ResponsiveAnalogRead.h"
#include <EasyTransfer.h>
#include "KnightRider.h"
#include "Comet.h"
#include "Bargraph.h"
#include "SwingController.h"



/*
██╗     ██╗ ██████╗ ██╗  ██╗████████╗
██║     ██║██╔════╝ ██║  ██║╚══██╔══╝
██║     ██║██║  ███╗███████║   ██║
██║     ██║██║   ██║██╔══██║   ██║
███████╗██║╚██████╔╝██║  ██║   ██║
╚══════╝╚═╝ ╚═════╝ ╚═╝  ╚═╝   ╚═╝

*/

// How many leds in your strip?
#define NUM_LEDS 134
#define NUM_LEDS_2 75
#define DATA_PIN 17
#define DATA_PIN_2 1

CRGB A_ledStrip[NUM_LEDS];
CRGB B_ledStrip[NUM_LEDS_2];
//MoveNeopixel moveNeopixel(A_ledStrip);
//MoveNeopixel moveNeopixelA(A_ledStrip);

//Neopixel Ledstrio Animation for Swing

// LightBulb for Animation for Time
KnightRider knightRider(CH);



/*
███████╗████████╗
██╔════╝╚══██╔══╝
█████╗     ██║   
██╔══╝     ██║   
███████╗   ██║   
╚══════╝   ╚═╝   
 */



/*
██╗     ███████╗███████╗████████╗    ██████╗  █████╗  ██████╗██╗  ██╗███████╗████████╗
██║     ██╔════╝██╔════╝╚══██╔══╝    ██╔══██╗██╔══██╗██╔════╝██║ ██╔╝██╔════╝╚══██╔══╝
██║     █████╗  █████╗     ██║       ██████╔╝███████║██║     █████╔╝ █████╗     ██║
██║     ██╔══╝  ██╔══╝     ██║       ██╔══██╗██╔══██║██║     ██╔═██╗ ██╔══╝     ██║
███████╗███████╗██║        ██║       ██║  ██║██║  ██║╚██████╗██║  ██╗███████╗   ██║
╚══════╝╚══════╝╚═╝        ╚═╝       ╚═╝  ╚═╝╚═╝  ╚═╝ ╚═════╝╚═╝  ╚═╝╚══════╝   ╚═╝
*/
// EasyTransfer sends Piezo Data from the Left Racket to Right Teensy
EasyTransfer ET;

struct SEND_DATA_STRUCTURE
{
  //put your variable definitions here for the data you want to send
  //THIS MUST BE EXACTLY THE SAME ON THE OTHER ARDUINO
  int16_t pz;
};
SEND_DATA_STRUCTURE mydata;
void blink();



// RF24 RECIVER 
const uint64_t ADRESS {0xF0F0F0F0D2LL};
const byte CHANNEL    {121};
const byte CE_PIN     {21};
const byte CSN_PIN    {20};

RF24 radio(CE_PIN, CSN_PIN);
ReciverData lr_rf24SensorData;
Reciver lr_reciver(radio, ADRESS, CHANNEL, lr_rf24SensorData);

// HIT Behaviour
const int RR_PIEZO_THERSHOLD_MIN{5};
const int RR_PIEZO_PEAKTRACK_MILLIS{3};
const int RR_PIEZO_AFTERSCHOCK_MILLIS{25};

PeakDetector   lr_PiezoDetector(RR_PIEZO_THERSHOLD_MIN, RR_PIEZO_PEAKTRACK_MILLIS, RR_PIEZO_AFTERSCHOCK_MILLIS);
Counter        lr_PiezoCounter;
InputSensorRaw lr_PiezoInput(lr_rf24SensorData);
Piezo          lr_Piezo(lr_PiezoDetector, lr_PiezoCounter, lr_PiezoInput);

// Motion Behaviour
Speed  lr_speed(lr_rf24SensorData);
Swing  lr_Swing(lr_rf24SensorData);
SF     lr_fusion;
Mahony lr_Mahony(lr_rf24SensorData, lr_fusion);

// Button Behaviour
Pressure lr_pressure(lr_rf24SensorData);

// Left Racket
Racket rightRacket(lr_Piezo, lr_speed, lr_Swing, lr_Mahony, lr_pressure);

// AudioVisual Behaviour for Swing without Ballcontact
Bargraph bargraph(A_ledStrip);
// AudioVisual Behaviour for Swing after Ballcontact
Comet comet(A_ledStrip);
SwingController swingController(comet,bargraph,rightRacket);

void setup()
{
  Serial.begin(9600);
 
  // while (!Serial )
  // {
  // }

  Serial8.begin(9600); // Open Serial8 for EaesyTransfer

  ET.begin(details(mydata), &Serial8);
  lr_reciver.setup();
  pinMode(24,OUTPUT);

}

void loop()
{
 
    blink();
    lr_reciver.loop();
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