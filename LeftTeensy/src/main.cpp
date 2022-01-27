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

 if(lt_Piezo.isHit())
 {
   lt_Piezo.countHit();

 }
  

 








  


  

}//End Loop