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
enum States { START, AS_L_RACKET, AS_L_TABLE, AS_R_TABLE, AS_R_RACKET, // Aufschlag
                     BW_L_TABLE, BW_L_RACKET, BW_R_TABLE, BW_R_RACKET, // Ballwechsel
                     TOTAL_COUNTER,                                    // Counter
                     FINISH_GAME
};

States state = START;

boolean checkOkHit(int , int , int , int );
void resetAllCounters();
void printGameStatus();
boolean isFehler();

int l_rCounter ;
int l_tCounter ;
int r_tCounter ;
int r_rCounter ;


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
  
              

<<<<<<< HEAD
  //leftRacket.setup();
  l_racketPiezoDetector.setThersholdMin(5);
  l_racketPiezoDetector.setPeakTrackMillis(10);
  l_racketPiezoDetector.setAfterSchockMillis(25);

  l_tablePiezoDetector.setThersholdMin(35);
  l_tablePiezoDetector.setPeakTrackMillis(10);
  l_tablePiezoDetector.setAfterSchockMillis(25);

  r_tablePiezoDetector.setThersholdMin(55);
  r_tablePiezoDetector.setPeakTrackMillis(10);
  r_tablePiezoDetector.setAfterSchockMillis(25);

  state = START;
=======
>>>>>>> main
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
  
<<<<<<< HEAD
  ET.receiveData();
 
=======
ET.receiveData();
>>>>>>> main

reciver.loop();

 lt_Piezo.loop();
 rr_Piezo.loop();
 rt_Piezo.loop();
 lr_Piezo.loop();

<<<<<<< HEAD
  //leftTable.loop();
  l_tablePiezoSmoother.update();
  l_tablePiezoDetector.loop();
  l_tablePiezoDetector.setInput(l_tablePiezoSmoother.getValue());
   
  // rightTable.loop();
  r_tablePiezoSmoother.update();
  r_tablePiezoDetector.loop();
  r_tablePiezoDetector.setInput(r_tablePiezoSmoother.getValue());
   
  //leftRacket.loop();
  l_racketPiezoDetector.loop();
  l_racketPiezoDetector.setInput(racketData.pz);

  //rightRacket.loop();
  r_racketPiezoDetector.loop();
  r_racketPiezoDetector.setInput(mydata.pz);



/*
  ██████╗  █████╗ ██╗     ██╗         ██╗  ██╗██╗████████╗
  ██╔══██╗██╔══██╗██║     ██║         ██║  ██║██║╚══██╔══╝
  ██████╔╝███████║██║     ██║         ███████║██║   ██║   
  ██╔══██╗██╔══██║██║     ██║         ██╔══██║██║   ██║   
  ██████╔╝██║  ██║███████╗███████╗    ██║  ██║██║   ██║   
  ╚═════╝ ╚═╝  ╚═╝╚══════╝╚══════╝    ╚═╝  ╚═╝╚═╝   ╚═╝   
*/

  //Left TABLE is hit
  if(l_tablePiezoDetector.getHit())
  {
    l_tablePiezoCounter.add();
    //Serial.print("Ball hits LEFT Table : " );
    //Serial.println( l_tablePiezoCounter.getSum());

  }

  //RIGHT TABLE is hit
  if(r_tablePiezoDetector.getHit())
  {  
    r_tablePiezoCounter.add();
    //Serial.print("Ball hits Right Table : " );
    //Serial.println( r_tablePiezoCounter.getSum());

  }

  // LEFT Racket is hit
  if(l_racketPiezoDetector.getHit())
  {
    l_racketPiezoCounter.add();
    //Serial.print("Ball hits LEFT Racket : " );
    //Serial.println( l_racketPiezoCounter.getSum());

  }

   // Right Racket is hit 
  if(r_racketPiezoDetector.getHit())
  {
    r_racketPiezoCounter.add();
   // Serial.print("Ball hits RGHT Racket : ");
   // Serial.println( r_racketPiezoCounter.getSum());
  }


// LEFT Racket 
// Do
l_rCounter = l_racketPiezoCounter.getSum();
l_tCounter = l_tablePiezoCounter.getSum();
r_tCounter = r_tablePiezoCounter.getSum();
r_rCounter = r_racketPiezoCounter.getSum();
=======
 if(lt_Piezo.isHit())
 {
   lt_Piezo.countHit();

 }
  

 








  

>>>>>>> main


 

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
  resetAllCounters();
  printGameStatus();
  state = AS_L_RACKET;

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
case AS_L_RACKET:
// Do
  

// Leave State:
    if ( l_rCounter == 1 )
  {

    Serial.println("AUFSCHLAG : BAll trift Left Racket");
    Serial.println("State 2.)AUFSCHLAG : Warte das BAll trift Left Table");

    printGameStatus();
    resetAllCounters();
    state = AS_L_TABLE;
   
  }

break;

case AS_L_TABLE:
//Do
// Leave State: 
    if ( l_tCounter == 1 )
  {
    

    Serial.println("AUFSCHLAG : BAll trift Left Table");
    Serial.println("State 3.) AUFSCHLAG : Warte das BAll trift Right Table");

    resetAllCounters();
    printGameStatus();
    state = AS_R_TABLE;
   
  }

  break;

case AS_R_TABLE:
  if (  r_tCounter == 1)
  {
    

    Serial.println("AUFSCHLAG : BAll trift Right Table");
    Serial.println("AUFSCHLAG : Warte das BAll trift Right Racket");

    resetAllCounters();
    printGameStatus();
    state = AS_R_RACKET;
   
  }
  break;

case AS_R_RACKET:
   if (  r_rCounter == 1)
  {
    printGameStatus();

     Serial.println("AUFSCHLAG : BAll trift Right Racket");
     Serial.println("AUFSCHLAG Erfolgreich");
     Serial.println("Starte Ballwechsel");

    


    resetAllCounters();
    state = BW_L_TABLE;
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
case BW_L_TABLE:
  if (checkOkHit(0, 1, 0, 0)) // Hit Left Table
  {
    resetAllCounters();
    state = BW_L_RACKET;
  }
  break;

case BW_L_RACKET:
  if (checkOkHit(1, 0, 0, 0)) // Hit Left RACket
  {
    resetAllCounters();
    state = BW_R_TABLE;
  }
  break;

case BW_R_TABLE:
  if (checkOkHit(0, 0, 1, 0)) // Hit Right Table
  {
    resetAllCounters();
    state = BW_R_RACKET;
  }
  break;

case BW_R_RACKET:
  if (checkOkHit(0, 0, 0, 1)) // Hit Right Racket
  {
    resetAllCounters();
    state = TOTAL_COUNTER;
  }
  break;

case TOTAL_COUNTER:
 
    // int totalBallWechselCounter++;
    state = BW_L_TABLE;
 
  break;

default:
  break;
}// end switch

}//End Loop


/*
 ██████╗ ██╗  ██╗        ██╗  ██╗██╗████████╗
██╔═══██╗██║ ██╔╝        ██║  ██║██║╚══██╔══╝
██║   ██║█████╔╝         ███████║██║   ██║   
██║   ██║██╔═██╗         ██╔══██║██║   ██║   
╚██████╔╝██║  ██╗███████╗██║  ██║██║   ██║   
 ╚═════╝ ╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝╚═╝   ╚═╝   
 */                                            
boolean checkOkHit(int l_rC, int l_tC, int r_tC, int r_rC )
{
  if( l_rCounter == l_rC && l_tCounter == l_tC && r_tCounter == r_tC && r_rCounter == r_rC)
  {
    
    return true;

  }else
  {
    return false;
  }

}
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
  if (l_rCounter > 1 || l_tCounter > 1 || r_tCounter > 1 || r_rCounter > 1)
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
  l_racketPiezoCounter.reset();
  l_tablePiezoCounter.reset();
  r_tablePiezoCounter.reset();
  r_racketPiezoCounter.reset();
}

void printGameStatus()
{
Serial.print(l_rCounter);
 Serial.print(l_tCounter);
 Serial.print(r_tCounter);
 Serial.print(r_rCounter);
 Serial.println("");

}