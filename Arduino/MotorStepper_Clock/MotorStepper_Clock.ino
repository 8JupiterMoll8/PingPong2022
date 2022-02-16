#include <AccelStepper.h>
#include <elapsedMillis.h>

elapsedMillis ms;
int incrementSpeed = 0;
int increaseStepperSpeed();

const byte X_STEPPER_STEP_PIN {41};
const byte X_STEPPER_DIR_PIN  {40};

const byte Y_STEPPER_STEP_PIN {39};
const byte Y_STEPPER_DIR_PIN  {38};

const byte A_STEPPER_STEP_PIN {37};
const byte A_STEPPER_DIR_PIN  {36};

AccelStepper stundenZeiger (1, X_STEPPER_STEP_PIN, X_STEPPER_DIR_PIN);
AccelStepper minutenZeiger (1, Y_STEPPER_STEP_PIN, Y_STEPPER_DIR_PIN);
AccelStepper sekundenZeiger(1, A_STEPPER_STEP_PIN, A_STEPPER_DIR_PIN);



int ar_Speed[4] = {500 , 1500, 50, 5000};


void setup()
{



  stundenZeiger.setMaxSpeed(12800);
  stundenZeiger.setSpeed(10000); // had to slow for my motor
  stundenZeiger.setAcceleration(100.0);

  minutenZeiger.setMaxSpeed(12800);
  minutenZeiger.setSpeed(10000); // had to slow for my motor
  minutenZeiger.setAcceleration(100.0);

  sekundenZeiger.setMaxSpeed(12800);
  sekundenZeiger.setSpeed(10000); // had to slow for my motor
  sekundenZeiger.setAcceleration(100.0);





}

void loop()
{


  //Xaxis.runToNewPosition(0);
  //Xaxis.runToNewPosition(500);

  //Yaxis.runToNewPosition(0);
  //Yaxis.runToNewPosition(500);






  //increaseStepperSpeed();
  randomStepperSpeed();


  stundenZeiger.setSpeed(incrementSpeed);
  minutenZeiger.setSpeed(incrementSpeed);
  sekundenZeiger.setSpeed(5000);

  stundenZeiger.runSpeed();
  minutenZeiger.runSpeed();
  sekundenZeiger.runSpeed();


}

int randomStepperSpeed()
{
  if (ms > 1000)
  {
    ms = 0;

    incrementSpeed = ar_Speed[random(0, 2)];
   // Xaxis.setCurrentPosition(0);



  }

}
int increaseStepperSpeed()
{
  if (ms > 1000)
  {
    ms = 0;
    ++incrementSpeed;


  }

}
