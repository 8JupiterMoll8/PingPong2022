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
ReciverData racketData;
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

  // while (!Serial )
  // {
  // }

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
  //  if (ET.receiveData())
  //  {
  //    // mydata.pz = mydata.pz;
  //  }

  // The Reciver fetch constanly Data from the Transmitter
  // to be used by the objects, which depend on them
  reciver.loop();

  
  l_tablePiezoSmoother.update();
  l_tablePiezoDetector.loop();
  l_tablePiezoDetector.setInput(l_tablePiezoSmoother.getValue());

  r_tablePiezoSmoother.update();
  r_tablePiezoDetector.loop();
  r_tablePiezoDetector.setInput(r_tablePiezoSmoother.getValue());

  l_racketPiezoDetector.loop();
  l_racketPiezoDetector.setInput(racketData.pz);

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
    Serial.print("Ball hits LEFT Table : " );
    Serial.println( l_tablePiezoCounter.getSum());

  }

  //RIGHT TABLE is hit
  if(r_tablePiezoDetector.getHit())
  {  
    r_tablePiezoCounter.add();
    Serial.print("Ball hits Right Table : " );
    Serial.println( r_tablePiezoCounter.getSum());

  }

  // LEFT Racket is hit
  if(l_racketPiezoDetector.getHit())
  {
    l_racketPiezoCounter.add();
    Serial.print("Ball hits LEFT Racket : " );
    Serial.println( l_racketPiezoCounter.getSum());

  }

   // Right Racket is hit 
  if(r_racketPiezoDetector.getHit())
  {
    r_racketPiezoCounter.add();
    Serial.print("Ball hits RGHT Racket : ");
    Serial.println( r_racketPiezoCounter.getSum());
  }


// LEFT Racket 
// Do
int l_rCounter = l_racketPiezoCounter.getSum();
int l_tCounter = l_tablePiezoCounter.getSum();
int r_tCounter = r_tablePiezoCounter.getSum();
int r_rCounter = r_racketPiezoCounter.getSum();
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
                     

/*
 █████╗ ██╗   ██╗███████╗███████╗ ██████╗██╗  ██╗██╗      █████╗  ██████╗ 
██╔══██╗██║   ██║██╔════╝██╔════╝██╔════╝██║  ██║██║     ██╔══██╗██╔════╝ 
███████║██║   ██║█████╗  ███████╗██║     ███████║██║     ███████║██║  ███╗
██╔══██║██║   ██║██╔══╝  ╚════██║██║     ██╔══██║██║     ██╔══██║██║   ██║
██║  ██║╚██████╔╝██║     ███████║╚██████╗██║  ██║███████╗██║  ██║╚██████╔╝
╚═╝  ╚═╝ ╚═════╝ ╚═╝     ╚══════╝ ╚═════╝╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝ ╚═════╝ 
*/     
//                                                                                                                                                    // States:
if( l_rCounter == 1 && l_tCounter == 0 && r_tCounter == 0 && r_rCounter == 0); // Hit Left Racket -  isHit(1,0,0,0);   
if( l_rCounter == 0 && l_tCounter == 1 && r_tCounter == 0 && r_rCounter == 0); // Hit Left Table  -  isHit(1,0,0,0);
if( l_rCounter == 0 && l_tCounter == 0 && r_tCounter == 1 && r_rCounter == 0); // Hit Right Table
if( l_rCounter == 0 && l_tCounter == 0 && r_tCounter == 0 && r_rCounter == 1); // Hit Right Racket
// States: Hit Left Racket >> Hit Left Table >> Hit Right Table >> Hit Right Racket
// >> Succseful Aufschlag 

/*
██████╗  █████╗ ██╗     ██╗     ██╗    ██╗███████╗ ██████╗██╗  ██╗███████╗███████╗██╗     
██╔══██╗██╔══██╗██║     ██║     ██║    ██║██╔════╝██╔════╝██║  ██║██╔════╝██╔════╝██║     
██████╔╝███████║██║     ██║     ██║ █╗ ██║█████╗  ██║     ███████║███████╗█████╗  ██║     
██╔══██╗██╔══██║██║     ██║     ██║███╗██║██╔══╝  ██║     ██╔══██║╚════██║██╔══╝  ██║     
██████╔╝██║  ██║███████╗███████╗╚███╔███╔╝███████╗╚██████╗██║  ██║███████║███████╗███████╗
╚═════╝ ╚═╝  ╚═╝╚══════╝╚══════╝ ╚══╝╚══╝ ╚══════╝ ╚═════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝
*/
if( l_rCounter == 0 && l_tCounter == 1 && r_tCounter == 0 && r_rCounter == 0); // Hit Left Table 
if( l_rCounter == 1 && l_tCounter == 0 && r_tCounter == 0 && r_rCounter == 0); // Hit Left Racket
if( l_rCounter == 0 && l_tCounter == 0 && r_tCounter == 1 && r_rCounter == 0); // Hit Right Table
if( l_rCounter == 0 && l_tCounter == 0 && r_tCounter == 0 && r_rCounter == 1); // Hit Right Racket
// States: Hit Left Table >> Hit Left Racket >> Hit Right Table >> Hit Right Racket
// >> Succseful Ballwechsel 

/*
███████╗███████╗██╗  ██╗██╗     ███████╗██████╗ 
██╔════╝██╔════╝██║  ██║██║     ██╔════╝██╔══██╗
█████╗  █████╗  ███████║██║     █████╗  ██████╔╝
██╔══╝  ██╔══╝  ██╔══██║██║     ██╔══╝  ██╔══██╗
██║     ███████╗██║  ██║███████╗███████╗██║  ██║
╚═╝     ╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚═╝  ╚═╝
*/
if( l_rCounter > 1 || l_tCounter > 1 || r_tCounter > 1 || r_rCounter > 1); // Restart Game
// Rule: The Ball does never hit two times at the Table or Racket and does fall to earth


/*
██████╗ ███████╗███████╗███████╗████████╗
██╔══██╗██╔════╝██╔════╝██╔════╝╚══██╔══╝
██████╔╝█████╗  ███████╗█████╗     ██║   
██╔══██╗██╔══╝  ╚════██║██╔══╝     ██║   
██║  ██║███████╗███████║███████╗   ██║   
╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝   ╚═╝   
                                         
*/
void resetAllCounters()
{
  l_racketPiezoCounter.reset();
  l_tablePiezoCounter.reset();
  r_tablePiezoCounter.reset();
  r_racketPiezoCounter.reset();
}
// Reset all Counters to Zero(0)








  

}//End Loop