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

struct RECEIVE_DATA_STRUCTURE
{
  //put your variable definitions here for the data you want to send
  //THIS MUST BE EXACTLY THE SAME ON THE OTHER ARDUINO
  int16_t pz;
} ;
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
PeakDetector l_racketPiezoDetector;
Counter      l_racketPiezoCounter(0);

/*
██████╗ ██╗ ██████╗ ██╗  ██╗████████╗    ██████╗  █████╗  ██████╗██╗  ██╗███████╗████████╗
██╔══██╗██║██╔════╝ ██║  ██║╚══██╔══╝    ██╔══██╗██╔══██╗██╔════╝██║ ██╔╝██╔════╝╚══██╔══╝
██████╔╝██║██║  ███╗███████║   ██║       ██████╔╝███████║██║     █████╔╝ █████╗     ██║   
██╔══██╗██║██║   ██║██╔══██║   ██║       ██╔══██╗██╔══██║██║     ██╔═██╗ ██╔══╝     ██║   
██║  ██║██║╚██████╔╝██║  ██║   ██║       ██║  ██║██║  ██║╚██████╗██║  ██╗███████╗   ██║   
╚═╝  ╚═╝╚═╝ ╚═════╝ ╚═╝  ╚═╝   ╚═╝       ╚═╝  ╚═╝╚═╝  ╚═╝ ╚═════╝╚═╝  ╚═╝╚══════╝   ╚═╝   
*/ 

PeakDetector r_racketPiezoDetector;
Counter      r_racketPiezoCounter(0);
                                                                                          
                                                                                                                                                                                                                                                                                                                                                     

/*
██╗     ███████╗███████╗████████╗    ████████╗ █████╗ ██████╗ ██╗     ███████╗
██║     ██╔════╝██╔════╝╚══██╔══╝    ╚══██╔══╝██╔══██╗██╔══██╗██║     ██╔════╝
██║     █████╗  █████╗     ██║          ██║   ███████║██████╔╝██║     █████╗  
██║     ██╔══╝  ██╔══╝     ██║          ██║   ██╔══██║██╔══██╗██║     ██╔══╝  
███████╗███████╗██║        ██║          ██║   ██║  ██║██████╔╝███████╗███████╗
╚══════╝╚══════╝╚═╝        ╚═╝          ╚═╝   ╚═╝  ╚═╝╚═════╝ ╚══════╝╚══════╝
 */
const int L_TABLE_PIEZO_PIN = A16;
ResponsiveAnalogRead l_tablePiezoSmoother(L_TABLE_PIEZO_PIN, false);
PeakDetector l_tablePiezoDetector;
Counter      l_tablePiezoCounter(0);

/*
██████╗ ██╗ ██████╗ ██╗  ██╗████████╗    ████████╗ █████╗ ██████╗ ██╗     ███████╗
██╔══██╗██║██╔════╝ ██║  ██║╚══██╔══╝    ╚══██╔══╝██╔══██╗██╔══██╗██║     ██╔════╝
██████╔╝██║██║  ███╗███████║   ██║          ██║   ███████║██████╔╝██║     █████╗  
██╔══██╗██║██║   ██║██╔══██║   ██║          ██║   ██╔══██║██╔══██╗██║     ██╔══╝  
██║  ██║██║╚██████╔╝██║  ██║   ██║          ██║   ██║  ██║██████╔╝███████╗███████╗
╚═╝  ╚═╝╚═╝ ╚═════╝ ╚═╝  ╚═╝   ╚═╝          ╚═╝   ╚═╝  ╚═╝╚═════╝ ╚══════╝╚══════╝
 */  
const byte R_TABLE_PIEZO_PIN = A17;
ResponsiveAnalogRead r_tablePiezoSmoother(R_TABLE_PIEZO_PIN, false);
PeakDetector r_tablePiezoDetector;
Counter      r_tablePiezoCounter(0);


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
 

  // The Reciver fetch constanly Data from the Transmitter
  // to be used by the objects, which depend on them
  reciver.loop();

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