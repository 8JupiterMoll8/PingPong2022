#include <Arduino.h>
#include <WS2812Serial.h>
#define USE_WS2812SERIAL
#include <FastLED.h>
#include <SPI.h>
#include "printf.h"
#include "RF24.h"
#include "PeaKDetector.hpp"
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
#include "Reciver.hpp"
#include "ReciverData.hpp"
#include "ResponsiveAnalogRead.h"
#include "KnightRider.h"
#include "Comet.h"
#include "Bargraph.h"
#include "SwingController.h"
#include "Racket.hpp" 



/*
██╗     ██╗ ██████╗ ██╗  ██╗████████╗
██║     ██║██╔════╝ ██║  ██║╚══██╔══╝
██║     ██║██║  ███╗███████║   ██║
██║     ██║██║   ██║██╔══██║   ██║
███████╗██║╚██████╔╝██║  ██║   ██║
╚══════╝╚═╝ ╚═════╝ ╚═╝  ╚═╝   ╚═╝

*/

// How many leds in your strip?
#define NUM_LEDS  134
#define NUM_LEDS_2 75
#define DATA_PIN    1
#define DATA_PIN_2 17

CRGB A_ledStrip[NUM_LEDS];
CRGB B_ledStrip[NUM_LEDS_2];
//MoveNeopixel moveNeopixel(A_ledStrip);
//MoveNeopixel moveNeopixelA(A_ledStrip);

//Neopixel Ledstrio Animation for Swing

// LightBulb for Animation for Time
KnightRider knightRider(CH);





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
  //float speed;
  // int32_t gx;
  // int32_t gz;
  // int32_t gy;
  // int32_t ax;
  // int32_t ay;
  // int32_t az;
    

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
const int RR_PIEZO_AFTERSCHOCK_MILLIS{50};

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
Racket leftRacket(lr_Piezo, lr_speed, lr_Swing, lr_Mahony, lr_pressure);

// AudioVisual Behaviour for Swing without Ballcontact
Bargraph bargraph(A_ledStrip);
// AudioVisual Behaviour for Swing after Ballcontact
Comet comet(A_ledStrip);
SwingController swingController(comet,bargraph,leftRacket);

void setup()
{
  Serial.begin(9600);
 
  // while (!Serial )
  // {
  // }

 // Init Light Bulb
  //setup_Dimmer();

  // Init WS2182B
  LEDS.addLeds<WS2812SERIAL, DATA_PIN, RGB>(A_ledStrip, NUM_LEDS).setCorrection(TypicalLEDStrip);
  //LEDS.addLeds<WS2812SERIAL, DATA_PIN_2, RGB>(B_ledStrip, 74);
  LEDS.setBrightness(255);

 // Init EasyTransfer
  Serial8.begin(115200); // Open Serial8 for EaesyTransfer
  ET.begin(details(mydata), &Serial8);

  // Init RF24 Reciver Lrft Racket
  lr_reciver.setup();

  // Blink Led Pin OutPut
  pinMode(24,OUTPUT);

}

void loop()
{
  // Teensy is On beacuse he is blinking
  blink();
  
  leftRacket.loop();
  // ET
  if(leftRacket.isHit())
  {

  //Serial.println("Hit");
  //mydata.pz  = lr_rf24SensorData.pz;
  //mydata.speed  = leftRacket.speed();
  // mydata.fsr = lr_rf24SensorData.fsr;
  // mydata.gx  = lr_rf24SensorData.gx;
  // mydata.gz  = lr_rf24SensorData.gz;
  // mydata.gy  = lr_rf24SensorData.gy;
  // mydata.ax  = lr_rf24SensorData.ax;
  // mydata.ay  = lr_rf24SensorData.ay;
  // mydata.az  = lr_rf24SensorData.az;
  
  }

  mydata.pz  = lr_rf24SensorData.pz;
  ET.sendData();

  // Loop RF24
  lr_reciver.loop();

  // Racket Audio Visual Behavuiut
  //leftRacket.loop();
  swingController.loop();
  FastLED.show();

  // KnightRider
  knightRider.loop();
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