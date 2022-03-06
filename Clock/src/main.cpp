#include <Arduino.h>
#include"Birnen.hpp"
#include "KnightRider.h"
#include "AccelStepper.h"
#include "Clock.h"
/*
 ██████╗██╗      ██████╗  ██████╗██╗  ██╗
██╔════╝██║     ██╔═══██╗██╔════╝██║ ██╔╝
██║     ██║     ██║   ██║██║     █████╔╝ 
██║     ██║     ██║   ██║██║     ██╔═██╗ 
╚██████╗███████╗╚██████╔╝╚██████╗██║  ██╗
 ╚═════╝╚══════╝ ╚═════╝  ╚═════╝╚═╝  ╚═╝
                                         
*/

  Clock clock;

/*
██╗     ██╗ ██████╗ ██╗  ██╗████████╗
██║     ██║██╔════╝ ██║  ██║╚══██╔══╝
██║     ██║██║  ███╗███████║   ██║
██║     ██║██║   ██║██╔══██║   ██║
███████╗██║╚██████╔╝██║  ██║   ██║
╚══════╝╚═╝ ╚═════╝ ╚═╝  ╚═╝   ╚═╝

*/


KnightRider knightRider(CH);


void setup() {
  setup_Dimmer();
}

void loop() 
{
 // CH1=CH2=CH3=CH4=CH5=CH6=CH7=CH8=30;
  // knightRider.loop();
  // knightRider.setSpeed(54);

 


  static float in = 4.712;
  float out;
 
 // do input, etc. here - as long as you don't pause, the LED will keep pulsing
  
  // in = in + 0.0001;
  // if (in > 10.995)
  //   in = 4.712;
  // out= sin(in) * 37.5 + 37.5 ;
  

  //   for (int i = 0; i < 8; i++)
  //   {
  //     static byte counter = 0;
  //     CH[i] = counter++;

  //     if(counter > 75) 
  //      counter = 0;
  //      delay(1000);
  //   }

  //          delay(10);

         for (i=95;i>10;i--)
          {
            CH1=CH2=CH3=CH4=CH5=CH6=CH7=CH8=i;
            delay(delay_time);
          }
          
           for (i=10;i<95;i++)
          {
            CH1=CH2=CH3=CH4=CH5=CH6=CH7=CH8=i;
            delay(delay_time);
          }



   

 

}