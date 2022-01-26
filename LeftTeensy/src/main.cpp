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
#include "Piezo.hpp"


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
PeakDetector lr_PiezoDetector;
Counter      lr_PiezoCounter;


/*
██████╗ ██╗ ██████╗ ██╗  ██╗████████╗    ██████╗  █████╗  ██████╗██╗  ██╗███████╗████████╗
██╔══██╗██║██╔════╝ ██║  ██║╚══██╔══╝    ██╔══██╗██╔══██╗██╔════╝██║ ██╔╝██╔════╝╚══██╔══╝
██████╔╝██║██║  ███╗███████║   ██║       ██████╔╝███████║██║     █████╔╝ █████╗     ██║   
██╔══██╗██║██║   ██║██╔══██║   ██║       ██╔══██╗██╔══██║██║     ██╔═██╗ ██╔══╝     ██║   
██║  ██║██║╚██████╔╝██║  ██║   ██║       ██║  ██║██║  ██║╚██████╗██║  ██╗███████╗   ██║   
╚═╝  ╚═╝╚═╝ ╚═════╝ ╚═╝  ╚═╝   ╚═╝       ╚═╝  ╚═╝╚═╝  ╚═╝ ╚═════╝╚═╝  ╚═╝╚══════╝   ╚═╝   
*/ 

PeakDetector r_racketPiezoDetector;
Counter      r_racketPiezoCounter;
                                                                                          
                                                                                                                                                                                                                                                                                                                                                     

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

PeakDetector         lt_PiezoDetector(LT_PIEZO_THERSHOLD_MIN,LT_PIEZO_PEAKTRACK_MILLIS,LT_PIEZO_AFTERSCHOCK_MILLIS);
ResponsiveAnalogRead lt_PiezoSmoother(LT_PIEZO_PIN, false);
Counter              lt_PiezoCounter;
Piezo                lt_Piezo(lt_PiezoDetector, lt_PiezoCounter, lt_PiezoSmoother);

/*
██████╗ ██╗ ██████╗ ██╗  ██╗████████╗    ████████╗ █████╗ ██████╗ ██╗     ███████╗
██╔══██╗██║██╔════╝ ██║  ██║╚══██╔══╝    ╚══██╔══╝██╔══██╗██╔══██╗██║     ██╔════╝
██████╔╝██║██║  ███╗███████║   ██║          ██║   ███████║██████╔╝██║     █████╗  
██╔══██╗██║██║   ██║██╔══██║   ██║          ██║   ██╔══██║██╔══██╗██║     ██╔══╝  
██║  ██║██║╚██████╔╝██║  ██║   ██║          ██║   ██║  ██║██████╔╝███████╗███████╗
╚═╝  ╚═╝╚═╝ ╚═════╝ ╚═╝  ╚═╝   ╚═╝          ╚═╝   ╚═╝  ╚═╝╚═════╝ ╚══════╝╚══════╝
 */  

/*PIEZO*/
const int RT_PIEZO_PIN               {A17};
const int RT_PIEZO_THERSHOLD_MIN      {35};
const int RT_PIEZO_PEAKTRACK_MILLIS   {10};
const int RT_PIEZO_AFTERSCHOCK_MILLIS {25};

PeakDetector         rt_PiezoDetector(RT_PIEZO_THERSHOLD_MIN,RT_PIEZO_PEAKTRACK_MILLIS,RT_PIEZO_AFTERSCHOCK_MILLIS);
ResponsiveAnalogRead rt_PiezoSmoother(RT_PIEZO_PIN, false);
Counter              rt_PiezoCounter;
Piezo                rt_Piezo(rt_PiezoDetector, rt_PiezoSmoother)             




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
  lt_Piezo.

  l_racketPiezoDetector.setThersholdMin(5);
  l_racketPiezoDetector.setPeakTrackMillis(10);
  l_racketPiezoDetector.setAfterSchockMillis(25);

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
  leftTable.loop();

  r_tablePiezoSmoother.update();
  r_tablePiezoDetector.loop();
  r_tablePiezoDetector.setInput(r_tablePiezoSmoother.getValue());

  l_racketPiezoDetector.loop();
  l_racketPiezoDetector.setInput(racketData.pz);

  r_racketPiezoDetector.loop();
  r_racketPiezoDetector.setInput(mydata.pz);





  //RIGHT TABLE
  if(r_tablePiezoDetector.getHit())
  {  
    r_tablePiezoCounter.add();
    Serial.print("Ball hits Right Table : " );
    Serial.println( r_tablePiezoCounter.getSum());

  }

  // LEFT Racket
  if(l_racketPiezoDetector.getHit())
  {
    l_racketPiezoCounter.add();
    Serial.print("Ball hits LEFT Racket : " );
    Serial.println( l_racketPiezoCounter.getSum());

  }

   // Right Racket
  if(r_racketPiezoDetector.getHit())
  {
    r_racketPiezoCounter.add();
    Serial.print("Ball hits RGHT Racket : ");
    Serial.println( r_racketPiezoCounter.getSum());
  }



  

}//End Loop