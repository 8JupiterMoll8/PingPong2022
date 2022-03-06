#include <Arduino.h>
// #include <WS2812Serial.h>
// #define USE_WS2812SERIAL
#include <FastLED.h>
#include <SPI.h>
#include "printf.h"
#include "RF24.h"
#include "Reciver.hpp"
#include "ReciverData.hpp"
#include "PeaKDetector.hpp"
#include "ResponsiveAnalogRead.h"
#include "Counter.hpp"
#include "I_InputSensorBhv.hpp"
#include "InputSensorRaw.hpp"
#include "InputSensorSmooth.hpp"
#include "Piezo.hpp"
#include <EasyTransfer.h>
#include "Swing.hpp"
#include "SensorFusion.h"
#include "Mahony.hpp"
#include "Pressure.hpp"
#include "Speed.hpp"
#include "Racket.hpp"
#include "Table.h"
#include "GameManager.h"
#include "MoveNeopixel.h"
#include "Comet.h"
#include "Bargraph.h"
#include "SwingController.h"
#include "PingPongManger.h"
#include "CometRaw.h"





/*
██╗     ██╗ ██████╗ ██╗  ██╗████████╗
██║     ██║██╔════╝ ██║  ██║╚══██╔══╝
██║     ██║██║  ███╗███████║   ██║
██║     ██║██║   ██║██╔══██║   ██║
███████╗██║╚██████╔╝██║  ██║   ██║
╚══════╝╚═╝ ╚═════╝ ╚═╝  ╚═╝   ╚═╝

*/

// How many leds in your strip?
const int NUM_LEDS  = 360;
CRGB LedStrip[NUM_LEDS];

CometRaw cometRaw(LedStrip,1);
CometRaw cometRaw2(LedStrip);






/*
██╗     ███████╗███████╗████████╗    ██████╗  █████╗  ██████╗██╗  ██╗███████╗████████╗
██║     ██╔════╝██╔════╝╚══██╔══╝    ██╔══██╗██╔══██╗██╔════╝██║ ██╔╝██╔════╝╚══██╔══╝
██║     █████╗  █████╗     ██║       ██████╔╝███████║██║     █████╔╝ █████╗     ██║
██║     ██╔══╝  ██╔══╝     ██║       ██╔══██╗██╔══██║██║     ██╔═██╗ ██╔══╝     ██║
███████╗███████╗██║        ██║       ██║  ██║██║  ██║╚██████╗██║  ██╗███████╗   ██║
╚══════╝╚══════╝╚═╝        ╚═╝       ╚═╝  ╚═╝╚═╝  ╚═╝ ╚═════╝╚═╝  ╚═╝╚══════╝   ╚═╝
*/

const uint64_t lr_ADRESS {0xF0F0F0F0D2LL};
const byte lr_CHANNEL    {121};
const byte lr_CE_PIN     {21};
const byte lr_CSN_PIN    {20};

RF24        lr_radio(lr_CE_PIN, lr_CSN_PIN);
ReciverData lr_rf24SensorData;
Reciver     lr_RF24_Reciver(lr_radio, lr_ADRESS, lr_CHANNEL, lr_rf24SensorData);


// HIT Behaviour
const int LR_PIEZO_THERSHOLD_MIN{5};
const int LR_PIEZO_PEAKTRACK_MILLIS{3};
const int LR_PIEZO_AFTERSCHOCK_MILLIS{25};

PeakDetector   lr_PiezoDetector(LR_PIEZO_THERSHOLD_MIN, LR_PIEZO_PEAKTRACK_MILLIS, LR_PIEZO_AFTERSCHOCK_MILLIS);
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
Bargraph bargraph2(LedStrip);
// AudioVisual Behaviour for Swing after Ballcontact
Comet comet2(LedStrip,1);
SwingController swingController2(comet2,bargraph2,leftRacket);





/*
██████╗ ██╗ ██████╗ ██╗  ██╗████████╗    ██████╗  █████╗  ██████╗██╗  ██╗███████╗████████╗
██╔══██╗██║██╔════╝ ██║  ██║╚══██╔══╝    ██╔══██╗██╔══██╗██╔════╝██║ ██╔╝██╔════╝╚══██╔══╝
██████╔╝██║██║  ███╗███████║   ██║       ██████╔╝███████║██║     █████╔╝ █████╗     ██║
██╔══██╗██║██║   ██║██╔══██║   ██║       ██╔══██╗██╔══██║██║     ██╔═██╗ ██╔══╝     ██║
██║  ██║██║╚██████╔╝██║  ██║   ██║       ██║  ██║██║  ██║╚██████╗██║  ██╗███████╗   ██║
╚═╝  ╚═╝╚═╝ ╚═════╝ ╚═╝  ╚═╝   ╚═╝       ╚═╝  ╚═╝╚═╝  ╚═╝ ╚═════╝╚═╝  ╚═╝╚══════╝   ╚═╝
*/
// RF24 RECIVER 
const uint64_t rr_ADRESS {0xF0F0F0F0E1LL};
const byte rr_CHANNEL    {125};
const byte rr_CE_PIN     {16}; 
const byte rr_CSN_PIN    {15}; 

   RF24 rr_radio(rr_CE_PIN, rr_CSN_PIN);
   ReciverData rr_rf24SensorData;
   Reciver rr_RF24_Reciver(rr_radio, rr_ADRESS, rr_CHANNEL, rr_rf24SensorData);

// HIT Behaviour
const int RR_PIEZO_THERSHOLD_MIN{5};
const int RR_PIEZO_PEAKTRACK_MILLIS{3};
const int RR_PIEZO_AFTERSCHOCK_MILLIS{25};

PeakDetector   rr_PiezoDetector(RR_PIEZO_THERSHOLD_MIN, RR_PIEZO_PEAKTRACK_MILLIS, RR_PIEZO_AFTERSCHOCK_MILLIS);
Counter        rr_PiezoCounter;
InputSensorRaw rr_PiezoInput(rr_rf24SensorData);
Piezo          rr_Piezo(rr_PiezoDetector, rr_PiezoCounter, rr_PiezoInput);

// Motion Behaviour
Speed  rr_speed(rr_rf24SensorData);
Swing  rr_Swing(rr_rf24SensorData);
SF     rr_fusion;
Mahony rr_Mahony(rr_rf24SensorData, rr_fusion);

// Button Behaviour
Pressure rr_pressure(rr_rf24SensorData);

// Left Racket
Racket rightRacket(rr_Piezo, rr_speed, rr_Swing, rr_Mahony, rr_pressure);

// AudioVisual Behaviour for Swing without Ballcontact
Bargraph bargraph(LedStrip);
// AudioVisual Behaviour for Swing after Ballcontact
Comet comet(LedStrip);
SwingController swingController(comet,bargraph,rightRacket);


/*
██╗     ███████╗███████╗████████╗    ████████╗ █████╗ ██████╗ ██╗     ███████╗
██║     ██╔════╝██╔════╝╚══██╔══╝    ╚══██╔══╝██╔══██╗██╔══██╗██║     ██╔════╝
██║     █████╗  █████╗     ██║          ██║   ███████║██████╔╝██║     █████╗
██║     ██╔══╝  ██╔══╝     ██║          ██║   ██╔══██║██╔══██╗██║     ██╔══╝
███████╗███████╗██║        ██║          ██║   ██║  ██║██████╔╝███████╗███████╗
╚══════╝╚══════╝╚═╝        ╚═╝          ╚═╝   ╚═╝  ╚═╝╚═════╝ ╚══════╝╚══════╝
 */


/*PIEZO*/
const int LT_PIEZO_PIN                  {A8};
const int LT_PIEZO_THERSHOLD_MIN        {50};
const int LT_PIEZO_PEAKTRACK_MILLIS      {5};
const int LT_PIEZO_AFTERSCHOCK_MILLIS   {500};

PeakDetector         lt_PiezoDetector(LT_PIEZO_THERSHOLD_MIN, LT_PIEZO_PEAKTRACK_MILLIS, LT_PIEZO_AFTERSCHOCK_MILLIS);
ResponsiveAnalogRead lt_PiezoSmoother(LT_PIEZO_PIN, false);
InputSensorSmooth    lt_PiezoInput(lt_PiezoSmoother);
Counter              lt_PiezoCounter;
Piezo lt_Piezo(lt_PiezoDetector, lt_PiezoCounter, lt_PiezoInput);

Table leftTable(lt_Piezo);

/*
██████╗ ██╗ ██████╗ ██╗  ██╗████████╗    ████████╗ █████╗ ██████╗ ██╗     ███████╗
██╔══██╗██║██╔════╝ ██║  ██║╚══██╔══╝    ╚══██╔══╝██╔══██╗██╔══██╗██║     ██╔════╝
██████╔╝██║██║  ███╗███████║   ██║          ██║   ███████║██████╔╝██║     █████╗
██╔══██╗██║██║   ██║██╔══██║   ██║          ██║   ██╔══██║██╔══██╗██║     ██╔══╝
██║  ██║██║╚██████╔╝██║  ██║   ██║          ██║   ██║  ██║██████╔╝███████╗███████╗
╚═╝  ╚═╝╚═╝ ╚═════╝ ╚═╝  ╚═╝   ╚═╝          ╚═╝   ╚═╝  ╚═╝╚═════╝ ╚══════╝╚══════╝
 */

/*PIEZO*/
const int RT_PIEZO_PIN                 {A9};
const int RT_PIEZO_THERSHOLD_MIN       {55};
const int RT_PIEZO_PEAKTRACK_MILLIS     {5};
const int RT_PIEZO_AFTERSCHOCK_MILLIS {500};

PeakDetector rt_PiezoDetector(RT_PIEZO_THERSHOLD_MIN, RT_PIEZO_PEAKTRACK_MILLIS, RT_PIEZO_AFTERSCHOCK_MILLIS);
ResponsiveAnalogRead rt_PiezoSmoother(RT_PIEZO_PIN, false);
InputSensorSmooth rt_PiezoInput(rt_PiezoSmoother);
Counter rt_PiezoCounter;
Piezo rt_Piezo(rt_PiezoDetector, rt_PiezoCounter, rt_PiezoInput); // Composition

Table rightTable(rt_Piezo);




/*
 ██████╗  █████╗ ███╗   ███╗███████╗    ███╗   ███╗ █████╗ ███╗   ██╗ █████╗  ██████╗ ███████╗██████╗ 
██╔════╝ ██╔══██╗████╗ ████║██╔════╝    ████╗ ████║██╔══██╗████╗  ██║██╔══██╗██╔════╝ ██╔════╝██╔══██╗
██║  ███╗███████║██╔████╔██║█████╗      ██╔████╔██║███████║██╔██╗ ██║███████║██║  ███╗█████╗  ██████╔╝
██║   ██║██╔══██║██║╚██╔╝██║██╔══╝      ██║╚██╔╝██║██╔══██║██║╚██╗██║██╔══██║██║   ██║██╔══╝  ██╔══██╗
╚██████╔╝██║  ██║██║ ╚═╝ ██║███████╗    ██║ ╚═╝ ██║██║  ██║██║ ╚████║██║  ██║╚██████╔╝███████╗██║  ██║
 ╚═════╝ ╚═╝  ╚═╝╚═╝     ╚═╝╚══════╝    ╚═╝     ╚═╝╚═╝  ╚═╝╚═╝  ╚═══╝╚═╝  ╚═╝ ╚═════╝ ╚══════╝╚═╝  ╚═╝
                                                                                                      
*/
  PingPongManger pingpongManager(leftRacket,rightRacket,leftTable,rightTable,comet);





/*
███████╗███████╗████████╗██╗   ██╗██████╗  ██╗██╗
██╔════╝██╔════╝╚══██╔══╝██║   ██║██╔══██╗██╔╝╚██╗
███████╗█████╗     ██║   ██║   ██║██████╔╝██║  ██║
╚════██║██╔══╝     ██║   ██║   ██║██╔═══╝ ██║  ██║
███████║███████╗   ██║   ╚██████╔╝██║     ╚██╗██╔╝
╚══════╝╚══════╝   ╚═╝    ╚═════╝ ╚═╝      ╚═╝╚═╝
 */
void setup()
{
  // Init Serial
  Serial.begin(9600);
  while (!Serial)
  {
  }

  // Init WS2182B
  LEDS.addLeds<SK9822, 26, 27, RGB, DATA_RATE_MHZ(12) >(LedStrip, NUM_LEDS);  // BGR ordering is typical
  LEDS.setBrightness(255);
  //LEDS.setMaxPowerInMilliWatts(300);

  // Init RF24 Reciver
  pinMode(lr_CE_PIN, OUTPUT);
  pinMode(lr_CSN_PIN, OUTPUT);
  pinMode(rr_CE_PIN, OUTPUT);
  pinMode(rr_CSN_PIN, OUTPUT);

  digitalWrite(rr_CSN_PIN, HIGH);
  lr_RF24_Reciver.setup();
  digitalWrite(lr_CSN_PIN, HIGH);
  rr_RF24_Reciver.setup();

}

/*
██╗      ██████╗  ██████╗ ██████╗  ██╗██╗
██║     ██╔═══██╗██╔═══██╗██╔══██╗██╔╝╚██╗
██║     ██║   ██║██║   ██║██████╔╝██║  ██║
██║     ██║   ██║██║   ██║██╔═══╝ ██║  ██║
███████╗╚██████╔╝╚██████╔╝██║     ╚██╗██╔╝
╚══════╝ ╚═════╝  ╚═════╝ ╚═╝      ╚═╝╚═╝
 */
void loop()
{

// Loop RF24
digitalWrite(lr_CSN_PIN, HIGH); // turn OFF lr_RF24_Reciver
rr_RF24_Reciver.loop();         // turn ON  rr_RF24_Reciver
digitalWrite(rr_CSN_PIN, HIGH); // turn OFF rr_RF24_Reciver
lr_RF24_Reciver.loop();         // turn ON  lr_RF24_Reciver

// Physical GameObjects
leftRacket.loop();
rightRacket.loop();
leftTable.loop();
rightTable.loop();


// GameManger for Aufschlag and BallwechselCounter
//pingpongManager.loop();

// Audiovisual Behavior for Rackets
//swingController.loop();
//swingController2.loop();
cometRaw.loop();
cometRaw2.loop();




  FastLED.show();
 




} // End Loop


      
