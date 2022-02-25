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
#include "InputSensorET.hpp"
#include "InputSensor_IC2.h"
#include "Piezo.hpp"
#include "ReciverDataET.hpp"
#include "Birnen.hpp"
#include <EasyTransfer.h>
#include "Swing.hpp"
#include "SensorFusion.h"
#include "Mahony.hpp"
#include "Pressure.hpp"
#include "Speed.hpp"
#include "Racket.hpp"
#include "RacketLeft.h"
#include "Table.h"
#include "GameManager.h"
#include "MoveNeopixel.h"
#include "KnightRider.h"
#include "Comet.h"
#include "Bargraph.h"
#include "SwingController.h"
#include "PingPongManger.h"
#include "Clock.h"




/*
██╗     ██╗ ██████╗ ██╗  ██╗████████╗
██║     ██║██╔════╝ ██║  ██║╚══██╔══╝
██║     ██║██║  ███╗███████║   ██║
██║     ██║██║   ██║██╔══██║   ██║
███████╗██║╚██████╔╝██║  ██║   ██║
╚══════╝╚═╝ ╚═════╝ ╚═╝  ╚═╝   ╚═╝

*/

// How many leds in your strip?
const int NUM_LEDS  = 288;

CRGB A_ledStrip[NUM_LEDS];

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
// IC2
#include"ReciverData_IC2.h"
TransmitData lr_IC2_SensorData;   

// Reciver EasyTransfer
EasyTransfer lr_ET;
// give a name to the group of data
RECEIVE_DATA_STRUCTURE lr_ET_SensorData;

//Hit 
const int LR_PIEZO_THERSHOLD_MIN{5};
const int LR_PIEZO_PEAKTRACK_MILLIS{3};
const int LR_PIEZO_AFTERSCHOCK_MILLIS{50};

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
Reciver rr_RF24_Reciver(radio, ADRESS, CHANNEL, rr_rf24SensorData);

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
const int LT_PIEZO_PIN                  {A8};
const int LT_PIEZO_THERSHOLD_MIN        {50};
const int LT_PIEZO_PEAKTRACK_MILLIS      {5};
const int LT_PIEZO_AFTERSCHOCK_MILLIS {500};

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
 ██████╗██╗      ██████╗  ██████╗██╗  ██╗
██╔════╝██║     ██╔═══██╗██╔════╝██║ ██╔╝
██║     ██║     ██║   ██║██║     █████╔╝ 
██║     ██║     ██║   ██║██║     ██╔═██╗ 
╚██████╗███████╗╚██████╔╝╚██████╗██║  ██╗
 ╚═════╝╚══════╝ ╚═════╝  ╚═════╝╚═╝  ╚═╝
                                         
*/
  // const byte X_STEPPER_STEP_PIN {41};
  // const byte X_STEPPER_DIR_PIN  {40};

  // const byte Y_STEPPER_STEP_PIN {39};
  // const byte Y_STEPPER_DIR_PIN  {38};

  // const byte A_STEPPER_STEP_PIN {37};
  // const byte A_STEPPER_DIR_PIN  {36};

  //AccelStepper stundenZeiger (1, X_STEPPER_STEP_PIN, X_STEPPER_DIR_PIN);
  //AccelStepper minutenZeiger (1, Y_STEPPER_STEP_PIN, Y_STEPPER_DIR_PIN);
  //AccelStepper sekundenZeiger(1, A_STEPPER_STEP_PIN, A_STEPPER_DIR_PIN);
  
  //Clock clock(stundenZeiger,minutenZeiger,sekundenZeiger);
    Clock clock;


/*
 ██████╗  █████╗ ███╗   ███╗███████╗    ███╗   ███╗ █████╗ ███╗   ██╗ █████╗  ██████╗ ███████╗██████╗ 
██╔════╝ ██╔══██╗████╗ ████║██╔════╝    ████╗ ████║██╔══██╗████╗  ██║██╔══██╗██╔════╝ ██╔════╝██╔══██╗
██║  ███╗███████║██╔████╔██║█████╗      ██╔████╔██║███████║██╔██╗ ██║███████║██║  ███╗█████╗  ██████╔╝
██║   ██║██╔══██║██║╚██╔╝██║██╔══╝      ██║╚██╔╝██║██╔══██║██║╚██╗██║██╔══██║██║   ██║██╔══╝  ██╔══██╗
╚██████╔╝██║  ██║██║ ╚═╝ ██║███████╗    ██║ ╚═╝ ██║██║  ██║██║ ╚████║██║  ██║╚██████╔╝███████╗██║  ██║
 ╚═════╝ ╚═╝  ╚═╝╚═╝     ╚═╝╚══════╝    ╚═╝     ╚═╝╚═╝  ╚═╝╚═╝  ╚═══╝╚═╝  ╚═╝ ╚═════╝ ╚══════╝╚═╝  ╚═╝
                                                                                                      
*/
//GameManager gameManger(leftRacket,rightRacket,leftTable,rightTable);
  PingPongManger pingpongManager(leftRacket,rightRacket,leftTable,rightTable,comet);
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
  LEDS.addLeds<SK9822, 26, 27, RGB, DATA_RATE_MHZ(15) >(A_ledStrip, NUM_LEDS);  // BGR ordering is typical
  LEDS.setBrightness(255);

  // Init EasyTransfer
  Serial8.begin(6000000);
  lr_ET.begin(details(lr_ET_SensorData), &Serial8);

  // Init RF24 Reciver Right Racket
  rr_RF24_Reciver.setup();

  // Init Clock
   clock.setup();
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
 lr_ET.receiveData();

// Loop RF24
rr_RF24_Reciver.loop();

//! Loop only one loop for each obeject
// Physical GameObjects
leftRacket.loop();
rightRacket.loop();
leftTable.loop();
rightTable.loop();


// GameManger for Aufschlag and BallwechselCounter
//gameManger.loop();
//pingpongManager.loop();

// Audiovisual Behavior for right Racket
// Bargraph and Comet right now
//swingController.loop();
//FastLED.show();

// if(leftRacket.isHit())
// {
//    Serial.println("HIT LEFT RACKET");
// }



clock.loop();

// BLINKING ON AND OFF WHEN BALL HITS RACKET RIGHT
if(leftRacket.isHit())
{
 Serial.println(lr_ET_SensorData.speed);
   

   usbMIDI.sendNoteOn(74,127,11);
   
        

        for (int j = 0; j < 200; j++)
        {

         A_ledStrip[j] = CRGB(255, 255, 255);
        }
}
else
{
      for (int j = 0; j < 200; j++)
        {

         A_ledStrip[j].nscale8(0);
        }
   usbMIDI.sendNoteOff(74,127,11);
}








//!This the Time Displayer his speed is dependet from 
//! From the amount of ballwechsel
// Light Bulb Speed Slow

  knightRider.loop();
  knightRider.setSpeed(25);





} // End Loop


      
