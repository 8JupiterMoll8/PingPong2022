#include <AccelStepper.h>
#include <elapsedMillis.h>

elapsedMillis ms;
int incrementSpeed = 0;
int increaseStepperSpeed();
  AccelStepper Xaxis(1, 2, 5); // pin 2 = step, pin 5 = direction
  AccelStepper Yaxis(1, 3, 6); // pin 2 = step, pin 5 = direction
  AccelStepper Zaxis(1, 12, 13); // pin 2 = step, pin 5 = direction



int ar_Speed[4] = {500 , 1500, 50, 5000};


void setup()
{
  


   Xaxis.setMaxSpeed(12800);
   Xaxis.setSpeed(10000); // had to slow for my motor
   Xaxis.setAcceleration(100.0);

   Yaxis.setMaxSpeed(12800);
   Yaxis.setSpeed(10000); // had to slow for my motor
   Yaxis.setAcceleration(100.0);

   Zaxis.setMaxSpeed(12800);
   Zaxis.setSpeed(10000); // had to slow for my motor
   Zaxis.setAcceleration(100.0);


 

   
}

void loop()
{   
  
  
    //Xaxis.runToNewPosition(0);
    //Xaxis.runToNewPosition(500);

    //Yaxis.runToNewPosition(0);
    //Yaxis.runToNewPosition(500);
    
    



  
    //increaseStepperSpeed();
   randomStepperSpeed();
  
  
  Xaxis.setSpeed(incrementSpeed);
  Yaxis.setSpeed(incrementSpeed);
  Zaxis.setSpeed(100);
  
  Xaxis.runSpeed();
  Yaxis.runSpeed();
  Zaxis.runSpeed();

   
}

int randomStepperSpeed()
{
  if(ms >1000)
  {
    ms= 0;
  
   incrementSpeed = ar_Speed[random(0, 2)];
   Xaxis.setCurrentPosition(0);
 

    
  }
  
}
int increaseStepperSpeed()
{
  if(ms >1000)
  {
    ms= 0;
    ++incrementSpeed;
 
    
  }
  
}
