#include <Arduino.h>
#include <WS2812Serial.h>
#define USE_WS2812SERIAL
#include <FastLED.h>
#include <SPI.h>
#include "printf.h"
#include "RF24.h"
#include "Reciver.hpp"
#include "ReciverData.hpp"
#include "PeaKDetector.hpp"
//#include "Racket.hpp"
#include "ResponsiveAnalogRead.h"
#include "Counter.hpp"
#include "I_InputSensorBhv.hpp"
#include "InputSensorRaw.hpp"
#include "InputSensorSmooth.hpp"
#include "InputSensorET.hpp"
#include "Piezo.hpp"
#include "ReciverDataET.hpp"
#include "Birnen.hpp"
#include <EasyTransfer.h>
#include "Swing.hpp"
#include "SensorFusion.h"
#include "Mahony.hpp"
#include "Pressure.hpp"
#include "Speed.hpp"
#include "RacketRight.hpp"
#include "RacketLeft.h"
#include "Table.h"
#include "GameManager.h"
#include "MoveNeopixel.h"
#include "KnightRider.h"
#include "Comet.h"
#include "Bargraph.h"
#include "SwingController.h"
#include "AudioVisualGameManager.h"




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
//KnightRider knightRider(CH);



/*
██╗     ███████╗███████╗████████╗    ██████╗  █████╗  ██████╗██╗  ██╗███████╗████████╗
██║     ██╔════╝██╔════╝╚══██╔══╝    ██╔══██╗██╔══██╗██╔════╝██║ ██╔╝██╔════╝╚══██╔══╝
██║     █████╗  █████╗     ██║       ██████╔╝███████║██║     █████╔╝ █████╗     ██║
██║     ██╔══╝  ██╔══╝     ██║       ██╔══██╗██╔══██║██║     ██╔═██╗ ██╔══╝     ██║
███████╗███████╗██║        ██║       ██║  ██║██║  ██║╚██████╗██║  ██╗███████╗   ██║
╚══════╝╚══════╝╚═╝        ╚═╝       ╚═╝  ╚═╝╚═╝  ╚═╝ ╚═════╝╚═╝  ╚═╝╚══════╝   ╚═╝
*/
// Reciver EasyTransfer
EasyTransfer ET;
// give a name to the group of data
RECEIVE_DATA_STRUCTURE lr_ET_SensorData;

//Hit 
const int LR_PIEZO_THERSHOLD_MIN{5};
const int LR_PIEZO_PEAKTRACK_MILLIS{3};
const int LR_PIEZO_AFTERSCHOCK_MILLIS{25};

PeakDetector  lr_PiezoDetector(LR_PIEZO_THERSHOLD_MIN, LR_PIEZO_PEAKTRACK_MILLIS, LR_PIEZO_AFTERSCHOCK_MILLIS);
Counter       lr_PiezoCounter;
InputSensorET lr_PiezoInput(lr_ET_SensorData);
Piezo lr_Piezo(lr_PiezoDetector, lr_PiezoCounter, lr_PiezoInput);

RacketLeft leftRacket(lr_Piezo);





/*
██████╗ ██╗ ██████╗ ██╗  ██╗████████╗    ██████╗  █████╗  ██████╗██╗  ██╗███████╗████████╗
██╔══██╗██║██╔════╝ ██║  ██║╚══██╔══╝    ██╔══██╗██╔══██╗██╔════╝██║ ██╔╝██╔════╝╚══██╔══╝
██████╔╝██║██║  ███╗███████║   ██║       ██████╔╝███████║██║     █████╔╝ █████╗     ██║
██╔══██╗██║██║   ██║██╔══██║   ██║       ██╔══██╗██╔══██║██║     ██╔═██╗ ██╔══╝     ██║
██║  ██║██║╚██████╔╝██║  ██║   ██║       ██║  ██║██║  ██║╚██████╗██║  ██╗███████╗   ██║
╚═╝  ╚═╝╚═╝ ╚═════╝ ╚═╝  ╚═╝   ╚═╝       ╚═╝  ╚═╝╚═╝  ╚═╝ ╚═════╝╚═╝  ╚═╝╚══════╝   ╚═╝
*/
// RF24 RECIVER 
const uint64_t ADRESS {0xF0F0F0F0E1LL};
const byte CHANNEL    {125};
const byte CE_PIN     {21};
const byte CSN_PIN    {20};

RF24 radio(CE_PIN, CSN_PIN);
ReciverData rr_rf24SensorData;
Reciver rr_reciver(radio, ADRESS, CHANNEL, rr_rf24SensorData);

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
RacketRight rightRacket(rr_Piezo, rr_speed, rr_Swing, rr_Mahony, rr_pressure);

// AudioVisual Behaviour for Swing without Ballcontact
Bargraph bargraph(A_ledStrip);
// AudioVisual Behaviour for Swing after Ballcontact
Comet comet(A_ledStrip);
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
const int LT_PIEZO_PIN{A16};
const int LT_PIEZO_THERSHOLD_MIN{35};
const int LT_PIEZO_PEAKTRACK_MILLIS{10};
const int LT_PIEZO_AFTERSCHOCK_MILLIS{25};

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
const int RT_PIEZO_PIN{A17};
const int RT_PIEZO_THERSHOLD_MIN{100};
const int RT_PIEZO_PEAKTRACK_MILLIS{10};
const int RT_PIEZO_AFTERSCHOCK_MILLIS{25};

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
//GameManager gameManger(leftRacket,rightRacket,leftTable,rightTable);
AudioVisualGameManager audiovisualGameManeger(leftRacket,rightRacket,leftTable,rightTable);
 //MovePixel movePixel(A_ledStrip);


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
  // Init Light Bulb
  setup_Dimmer();

  // Init WS2182B
  LEDS.addLeds<WS2812SERIAL, DATA_PIN, RGB>(A_ledStrip, NUM_LEDS).setCorrection(TypicalLEDStrip);
  LEDS.addLeds<WS2812SERIAL, DATA_PIN_2, RGB>(B_ledStrip, 74);
  LEDS.setBrightness(255);

  // Init EasyTransfer
  Serial8.begin(9600);
  ET.begin(details(lr_ET_SensorData), &Serial8);

  // Init RF24 Reciver Right Racket
  rr_reciver.setup();
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
// Loop EasyTransfer
  ET.receiveData();
// Loop RF24
  rr_reciver.loop();
//! Loop only one loop for each obeject
// Physical GameObjects
leftRacket.loop();
rightRacket.loop();
leftTable.loop();
rightTable.loop();
// GameManger for Aufschlag and BallwechselCounter
//gameManger.loop();
audiovisualGameManeger.loop();
// Audiovisual Behavior for right Racket
// Bargraph and Comet right now
swingController.loop();
FastLED.show();


//!This the Time Displayer his speed is dependet from 
//! From the amount of ballwechsel
// Light Bulb Speed Slow
  // static elapsedMillis ms_speed;
  // knightRider.loop();
  // if (ms_speed > 1000)
  // {
  //   ms_speed = 0;
    
  //   static int increment = 0;
  //   increment = increment + 10;
  //   Serial.println(increment);
  //   knightRider.setSpeed(increment);
  // }

  // Physics Eigen
  // moveNeopixel.loop();
  // moveNeopixelA.loop();

  // moveNeopixel.intervall = 50;
  // moveNeopixel.blue = 0;
  // moveNeopixel.red = 255;
  // moveNeopixel.green = 100;

  // moveNeopixelA.intervall = 250;
  // moveNeopixelA.blue = 255;
  // moveNeopixelA.red = 255;
  // moveNeopixelA.green = 100;


  




  
 
 




  



  // Representing Time Speed Light Bulb
 // knightRider.loop();
  //knightRider.setSpeed(60);

  // 
  //bargraph.loop();



  //TODO AudioVisual the energy of the Swing
  //comet.loop();

  

} // End Loop

