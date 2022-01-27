#include <Arduino.h>
#include <EasyTransfer.h>
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


/*
██████╗ ███████╗██████╗ ██╗  ██╗
██╔══██╗██╔════╝╚════██╗██║  ██║
██████╔╝█████╗   █████╔╝███████║
██╔══██╗██╔══╝  ██╔═══╝ ╚════██║
██║  ██║██║     ███████╗     ██║
╚═╝  ╚═╝╚═╝     ╚══════╝     ╚═╝
*/
RF24 radio(21, 20); //CE pin, CSN pin
const uint64_t ADRESS{0xF0F0F0F0E1LL};
const byte CHANNEL{125};
ReciverData racketData;// Observer 
Reciver reciver(radio, ADRESS, CHANNEL, racketData);


/*
███████╗████████╗
██╔════╝╚══██╔══╝
█████╗     ██║   
██╔══╝     ██║   
███████╗   ██║   
╚══════╝   ╚═╝   
 */
EasyTransfer ET;
//give a name to the group of data
RECEIVE_DATA_STRUCTURE mydata;

/*
██╗     ███████╗███████╗████████╗    ██████╗  █████╗  ██████╗██╗  ██╗███████╗████████╗
██║     ██╔════╝██╔════╝╚══██╔══╝    ██╔══██╗██╔══██╗██╔════╝██║ ██╔╝██╔════╝╚══██╔══╝
██║     █████╗  █████╗     ██║       ██████╔╝███████║██║     █████╔╝ █████╗     ██║   
██║     ██╔══╝  ██╔══╝     ██║       ██╔══██╗██╔══██║██║     ██╔═██╗ ██╔══╝     ██║   
███████╗███████╗██║        ██║       ██║  ██║██║  ██║╚██████╗██║  ██╗███████╗   ██║   
╚══════╝╚══════╝╚═╝        ╚═╝       ╚═╝  ╚═╝╚═╝  ╚═╝ ╚═════╝╚═╝  ╚═╝╚══════╝   ╚═╝   
*/                                                                                      
const int LR_PIEZO_THERSHOLD_MIN       {5};
const int LR_PIEZO_PEAKTRACK_MILLIS    {3};
const int LR_PIEZO_AFTERSCHOCK_MILLIS {25};

PeakDetector   lr_PiezoDetector(LR_PIEZO_THERSHOLD_MIN,LR_PIEZO_PEAKTRACK_MILLIS,LR_PIEZO_AFTERSCHOCK_MILLIS);
Counter        lr_PiezoCounter;
InputSensorET  lr_PiezoInput(mydata);
Piezo          lr_Piezo(lr_PiezoDetector, lr_PiezoCounter,lr_PiezoInput );


/*
██████╗ ██╗ ██████╗ ██╗  ██╗████████╗    ██████╗  █████╗  ██████╗██╗  ██╗███████╗████████╗
██╔══██╗██║██╔════╝ ██║  ██║╚══██╔══╝    ██╔══██╗██╔══██╗██╔════╝██║ ██╔╝██╔════╝╚══██╔══╝
██████╔╝██║██║  ███╗███████║   ██║       ██████╔╝███████║██║     █████╔╝ █████╗     ██║   
██╔══██╗██║██║   ██║██╔══██║   ██║       ██╔══██╗██╔══██║██║     ██╔═██╗ ██╔══╝     ██║   
██║  ██║██║╚██████╔╝██║  ██║   ██║       ██║  ██║██║  ██║╚██████╗██║  ██╗███████╗   ██║   
╚═╝  ╚═╝╚═╝ ╚═════╝ ╚═╝  ╚═╝   ╚═╝       ╚═╝  ╚═╝╚═╝  ╚═╝ ╚═════╝╚═╝  ╚═╝╚══════╝   ╚═╝   
*/ 

const int RR_PIEZO_THERSHOLD_MIN       {5};
const int RR_PIEZO_PEAKTRACK_MILLIS    {3};
const int RR_PIEZO_AFTERSCHOCK_MILLIS {25};

PeakDetector   rr_PiezoDetector(RR_PIEZO_THERSHOLD_MIN,RR_PIEZO_PEAKTRACK_MILLIS,RR_PIEZO_AFTERSCHOCK_MILLIS);
Counter        rr_PiezoCounter;
InputSensorRaw rr_PiezoInput(racketData);
Piezo          rr_Piezo(rr_PiezoDetector, rr_PiezoCounter,rr_PiezoInput );//Composition   
                                                                                          
                                                                                                                                                                                                                                                                                                                                                     

/*
██╗     ███████╗███████╗████████╗    ████████╗ █████╗ ██████╗ ██╗     ███████╗
██║     ██╔════╝██╔════╝╚══██╔══╝    ╚══██╔══╝██╔══██╗██╔══██╗██║     ██╔════╝
██║     █████╗  █████╗     ██║          ██║   ███████║██████╔╝██║     █████╗  
██║     ██╔══╝  ██╔══╝     ██║          ██║   ██╔══██║██╔══██╗██║     ██╔══╝  
███████╗███████╗██║        ██║          ██║   ██║  ██║██████╔╝███████╗███████╗
╚══════╝╚══════╝╚═╝        ╚═╝          ╚═╝   ╚═╝  ╚═╝╚═════╝ ╚══════╝╚══════╝
 */
/*PIEZO*/
const int LT_PIEZO_PIN               {A16};
const int LT_PIEZO_THERSHOLD_MIN      {35};
const int LT_PIEZO_PEAKTRACK_MILLIS   {10};
const int LT_PIEZO_AFTERSCHOCK_MILLIS {25};

PeakDetector         lt_PiezoDetector(LT_PIEZO_THERSHOLD_MIN, LT_PIEZO_PEAKTRACK_MILLIS, LT_PIEZO_AFTERSCHOCK_MILLIS);
ResponsiveAnalogRead lt_PiezoSmoother(LT_PIEZO_PIN, false);
InputSensorSmooth    lt_PiezoInput(lt_PiezoSmoother);
Counter              lt_PiezoCounter;
Piezo                lt_Piezo(lt_PiezoDetector, lt_PiezoCounter, lt_PiezoInput );//Composition   

/*
██████╗ ██╗ ██████╗ ██╗  ██╗████████╗    ████████╗ █████╗ ██████╗ ██╗     ███████╗
██╔══██╗██║██╔════╝ ██║  ██║╚══██╔══╝    ╚══██╔══╝██╔══██╗██╔══██╗██║     ██╔════╝
██████╔╝██║██║  ███╗███████║   ██║          ██║   ███████║██████╔╝██║     █████╗  
██╔══██╗██║██║   ██║██╔══██║   ██║          ██║   ██╔══██║██╔══██╗██║     ██╔══╝  
██║  ██║██║╚██████╔╝██║  ██║   ██║          ██║   ██║  ██║██████╔╝███████╗███████╗
╚═╝  ╚═╝╚═╝ ╚═════╝ ╚═╝  ╚═╝   ╚═╝          ╚═╝   ╚═╝  ╚═╝╚═════╝ ╚══════╝╚══════╝
 */  

/*PIEZO*/
const int RT_PIEZO_PIN                {A17};
const int RT_PIEZO_THERSHOLD_MIN      {100};
const int RT_PIEZO_PEAKTRACK_MILLIS   {10};
const int RT_PIEZO_AFTERSCHOCK_MILLIS {25};

PeakDetector         rt_PiezoDetector(RT_PIEZO_THERSHOLD_MIN, RT_PIEZO_PEAKTRACK_MILLIS, RT_PIEZO_AFTERSCHOCK_MILLIS);
ResponsiveAnalogRead rt_PiezoSmoother(RT_PIEZO_PIN, false);
InputSensorSmooth    rt_PiezoInput(rt_PiezoSmoother);
Counter              rt_PiezoCounter;
Piezo                rt_Piezo(rt_PiezoDetector, rt_PiezoCounter, rt_PiezoInput); //Composition           





/*
███████╗████████╗ █████╗ ████████╗███████╗███████╗
██╔════╝╚══██╔══╝██╔══██╗╚══██╔══╝██╔════╝██╔════╝
███████╗   ██║   ███████║   ██║   █████╗  ███████╗
╚════██║   ██║   ██╔══██║   ██║   ██╔══╝  ╚════██║
███████║   ██║   ██║  ██║   ██║   ███████╗███████║
╚══════╝   ╚═╝   ╚═╝  ╚═╝   ╚═╝   ╚══════╝╚══════╝
                                                  
*/
enum States { START, lr_AS, lt_AS, rt_AS, rr_AS, // Aufschlag von Links
                     lt_BW, lr_BW, rt_BW, rr_BW, // Ballwechsel
                     count_BW,                   // Counter
              FINISH_GAME
};

States state = START;

boolean checkOkHit(int , int , int , int );
void resetAllCounters();
void printGameStatus();
boolean isFehler();

int lr_Counter ;
int lt_Counter ;
int rt_Counter ;
int rr_Counter ;


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
  Serial.begin(9600);
  Serial8.begin(9600);

  while (!Serial )
  {
  }

  ET.begin(details(mydata), &Serial8);

  reciver.setup();
  
              

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
  

ET.receiveData();

reciver.loop();

 lt_Piezo.loop();
 rr_Piezo.loop();
 rt_Piezo.loop();
 lr_Piezo.loop();





switch (state)
{
/*
███████╗████████╗ █████╗ ██████╗ ████████╗
██╔════╝╚══██╔══╝██╔══██╗██╔══██╗╚══██╔══╝
███████╗   ██║   ███████║██████╔╝   ██║   
╚════██║   ██║   ██╔══██║██╔══██╗   ██║   
███████║   ██║   ██║  ██║██║  ██║   ██║   
╚══════╝   ╚═╝   ╚═╝  ╚═╝╚═╝  ╚═╝   ╚═╝   
                                          
*/
case START:

  Serial.println("STARTE SPIEL");
  Serial.println("State 1.) AUFSCHLAG : Warte dass, der Ball trift Left Racket trift");
  
  //printGameStatus();
  resetAllCounters();

  //Leave State:
  state = lr_AS;

  // Leave State:
  break;
/*
 █████╗ ██╗   ██╗███████╗███████╗ ██████╗██╗  ██╗██╗      █████╗  ██████╗ 
██╔══██╗██║   ██║██╔════╝██╔════╝██╔════╝██║  ██║██║     ██╔══██╗██╔════╝ 
███████║██║   ██║█████╗  ███████╗██║     ███████║██║     ███████║██║  ███╗
██╔══██║██║   ██║██╔══╝  ╚════██║██║     ██╔══██║██║     ██╔══██║██║   ██║
██║  ██║╚██████╔╝██║     ███████║╚██████╗██║  ██║███████╗██║  ██║╚██████╔╝
╚═╝  ╚═╝ ╚═════╝ ╚═╝     ╚══════╝ ╚═════╝╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝ ╚═════╝ 
*/
// States: Hit Left Racket >> Hit Left Table >> Hit Right Table >> Hit Right Racket
// >> Succseful Aufschlag
case lr_AS:
  // Do

  //Leave State:
  if (lr_Piezo.hitSum() == 1)
  {
    Serial.println("AUFSCHLAG : BAll trift Left Racket");
    Serial.println("State 2.)AUFSCHLAG : Warte das BAll trift Left Table");

    //printGameStatus();
    resetAllCounters();
    state = lt_AS;
  }

  break;

case lt_AS:
  //Do
  // Leave State:
  if (lt_Piezo.hitSum() == 1)
  {
    Serial.println("AUFSCHLAG : BAll trift Left Table");
    Serial.println("State 3.) AUFSCHLAG : Warte das BAll trift Right Table");

    //printGameStatus();
    resetAllCounters();
    state = rt_AS;
  }

  break;

case rt_AS:
  //Do
  // Leave State:
  if (rt_Piezo.hitSum() == 1)
  {

    Serial.println("AUFSCHLAG : BAll trift Right Table");
    Serial.println("AUFSCHLAG : Warte das BAll trift Right Racket");

    //printGameStatus();
    resetAllCounters();
    state = rr_AS;
  }
  break;

case rr_AS:
  //Do
  // Leave State:
  if (rr_Piezo.hitSum() == 1)
  {
    Serial.println("AUFSCHLAG : BAll trift Right Racket");
    Serial.println("AUFSCHLAG Erfolgreich");
    Serial.println("Starte Ballwechsel");
    Serial.println("BAllWechsel : Warte das BAll trift Left Table");

    //printGameStatus();
    resetAllCounters();
    state = lt_BW;
  }
  break;

/*
██████╗  █████╗ ██╗     ██╗     ██╗    ██╗███████╗ ██████╗██╗  ██╗███████╗███████╗██╗     
██╔══██╗██╔══██╗██║     ██║     ██║    ██║██╔════╝██╔════╝██║  ██║██╔════╝██╔════╝██║     
██████╔╝███████║██║     ██║     ██║ █╗ ██║█████╗  ██║     ███████║███████╗█████╗  ██║     
██╔══██╗██╔══██║██║     ██║     ██║███╗██║██╔══╝  ██║     ██╔══██║╚════██║██╔══╝  ██║     
██████╔╝██║  ██║███████╗███████╗╚███╔███╔╝███████╗╚██████╗██║  ██║███████║███████╗███████╗
╚═════╝ ╚═╝  ╚═╝╚══════╝╚══════╝ ╚══╝╚══╝ ╚══════╝ ╚═════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝
*/
case lt_BW:
  //Do
  // Leave State:
  if (lt_Piezo.hitSum() == 1) // Hit Left Table
  {
    usbMIDI.sendNoteOff(74,127,2);

    Serial.println("Ballwechsel : Warte das BAll trift Left Racket");

    resetAllCounters();
    state = lr_BW;
  }
  break;

case lr_BW:
  //Dou
  // Leave State:
  if (lr_Piezo.hitSum() == 1) // Hit Left RACket
  {
    usbMIDI.sendNoteOn(54,127,2);
    Serial.println("Ballwechsel : Warte das BAll trift Right Table");

    resetAllCounters();
    state = rt_BW;
  }
  break;

case rt_BW:
  //Do
  
  // Leave State:
  if (rt_Piezo.hitSum() == 1) // Hit Right Table
  {
    usbMIDI.sendNoteOff(54,0,2);
    Serial.println("Ballwechsel : Warte das BAll trift Right RAcket");

    resetAllCounters();
    state = rr_BW;

  }
  break;

case rr_BW:
  //Do
  // Leave State:
  if (rr_Piezo.hitSum() == 1) // Hit Right Racket
  {
    usbMIDI.sendNoteOn(74,127,2);
    Serial.println("Ballwechsel : Erfolgreich");

    resetAllCounters();
    state = count_BW;

  }
  break;

case count_BW:
  //Do
  static int totalBallWechselCounter =0;
  Serial.print("BAllWechsel Total : ");
  Serial.println(++totalBallWechselCounter);

  Serial.println("BAllWechsel : Warte das BAll trift Left Table");

  // Leave State:
  state = lt_BW;
  break;

default:
  break;
} // end switch

} //End Loop


/*
███████╗███████╗██╗  ██╗██╗     ███████╗██████╗ 
██╔════╝██╔════╝██║  ██║██║     ██╔════╝██╔══██╗
█████╗  █████╗  ███████║██║     █████╗  ██████╔╝
██╔══╝  ██╔══╝  ██╔══██║██║     ██╔══╝  ██╔══██╗
██║     ███████╗██║  ██║███████╗███████╗██║  ██║
╚═╝     ╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚═╝  ╚═╝
*/
// Restart Game
// Rule: The Ball does never hit two times at the Table or Racket and does fall to earth
boolean isFehler()
{   
  //if(leftRacket.isDoubleHit() || leftTable.isDoubleHit() || rightTable.isDoubleHit() || rightRacket.isDoubeleHit())
  if (lr_Counter > 1 || lt_Counter > 1 || rt_Counter > 1 || rr_Counter > 1)
  {
 
    return true;

  }else
  {
    return false;
  }
   
}
/*
██████╗ ███████╗███████╗███████╗████████╗
██╔══██╗██╔════╝██╔════╝██╔════╝╚══██╔══╝
██████╔╝█████╗  ███████╗█████╗     ██║   
██╔══██╗██╔══╝  ╚════██║██╔══╝     ██║   
██║  ██║███████╗███████║███████╗   ██║   
╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝   ╚═╝   
                                         
*/
// Reset all Counters to Zero(0)
void resetAllCounters()
{
  lr_Piezo.resetHitSum();
  lt_Piezo.resetHitSum();
  rt_Piezo.resetHitSum();
  rr_Piezo.resetHitSum();
}

void printGameStatus()
{
 Serial.print(lr_Counter);
 Serial.print(lt_Counter);
 Serial.print(rt_Counter);
 Serial.print(rr_Counter);
 Serial.println("");

}