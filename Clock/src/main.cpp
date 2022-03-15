#include <Arduino.h>
#include"Birnen.hpp"
#include "KnightRider.h"
#include "AccelStepper.h"
#include "Clock.h"
#include "IMoveBehaviour.h"
#include "MoveConstant.h"
#include "FadeAll.h"
#include "Fader.h"
#include <EasyTransfer.h>

/*
███████╗ █████╗ ███████╗██╗   ██╗████████╗██████╗  █████╗ ███╗   ██╗███████╗███████╗███████╗██████╗ 
██╔════╝██╔══██╗██╔════╝╚██╗ ██╔╝╚══██╔══╝██╔══██╗██╔══██╗████╗  ██║██╔════╝██╔════╝██╔════╝██╔══██╗
█████╗  ███████║███████╗ ╚████╔╝    ██║   ██████╔╝███████║██╔██╗ ██║███████╗█████╗  █████╗  ██████╔╝
██╔══╝  ██╔══██║╚════██║  ╚██╔╝     ██║   ██╔══██╗██╔══██║██║╚██╗██║╚════██║██╔══╝  ██╔══╝  ██╔══██╗
███████╗██║  ██║███████║   ██║      ██║   ██║  ██║██║  ██║██║ ╚████║███████║██║     ███████╗██║  ██║
╚══════╝╚═╝  ╚═╝╚══════╝   ╚═╝      ╚═╝   ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═══╝╚══════╝╚═╝     ╚══════╝╚═╝  ╚═╝
                                                                                                    
*/

EasyTransfer ET;
struct ET_ReciverData
{
   uint32_t leftRacketSpeed;
   uint32_t rightRacketSpeed;
   uint8_t  rightRacketHit;
   uint8_t  leftRacketHit;
   uint8_t  leftTableHit;
   uint8_t  rightTableHit;
};

//give a name to the group of data
ET_ReciverData mydata;


/*
 ██████╗██╗      ██████╗  ██████╗██╗  ██╗
██╔════╝██║     ██╔═══██╗██╔════╝██║ ██╔╝
██║     ██║     ██║   ██║██║     █████╔╝ 
██║     ██║     ██║   ██║██║     ██╔═██╗ 
╚██████╗███████╗╚██████╔╝╚██████╗██║  ██╗
 ╚═════╝╚══════╝ ╚═════╝  ╚═════╝╚═╝  ╚═╝
                                         
*/
    const byte X_STEPPER_STEP_PIN  {3};
    const byte X_STEPPER_DIR_PIN   {4};

    const byte Y_STEPPER_STEP_PIN  {5};
    const byte Y_STEPPER_DIR_PIN   {6};

    const byte A_STEPPER_STEP_PIN  {7};
    const byte A_STEPPER_DIR_PIN   {8};

    AccelStepper l_zeiger (1, X_STEPPER_STEP_PIN, X_STEPPER_DIR_PIN);
    MoveConstant lz_moveConstant(l_zeiger);
    IMoveBehaviour *lz_MoveConstant = &lz_moveConstant;






 // Clock clock;

/*
██╗     ██╗ ██████╗ ██╗  ██╗████████╗
██║     ██║██╔════╝ ██║  ██║╚══██╔══╝
██║     ██║██║  ███╗███████║   ██║
██║     ██║██║   ██║██╔══██║   ██║
███████╗██║╚██████╔╝██║  ██║   ██║
╚══════╝╚═╝ ╚═════╝ ╚═╝  ╚═╝   ╚═╝

*/


KnightRider l_knightRider(l_CH);
KnightRider r_knightRider(CH);
FadeAll fadeAll(l_CH,CH);
Fader fader;


void setup() {
  Serial.begin(115200);
  Serial1.begin(115200);
  while(!Serial)
  {

  }
  ET.begin(details(mydata), &Serial1);

  // INIT AC BULBS 240V PHASE CONTROLLER
  setup_Dimmer();
  Serial.println("AC DIMMER 2");
  

  //lz_moveConstant.setup();

}

void loop() 
{
//AC 240V BULBS

 //l_knightRider.loop();
 //l_knightRider.setSpeed(1000);
 //l_knightRider.setBrightness(30);

 //r_knightRider.loop();
 //r_knightRider.setSpeed(1000);
 //r_knightRider.setBrightness(30);



 //fadeAll.loop();


//lz_MoveConstant->loop();
//lz_MoveConstant->setSpeed(7000);
//Serial.println(mydata.leftRacketSpeed);
// STATE: Wait
if (ET.receiveData())
{

  if (mydata.rightTableHit == 1)
    Serial.println("HitRighTable ");

  if (mydata.leftTableHit == 1)
    Serial.println("HitLefttTable ");

  if (mydata.rightRacketHit == 1)
  {
    static int count = 0;
    Serial.print("HitRightRacket : ");
    Serial.println(count++);
  }

  if (mydata.leftRacketHit == 1)
  {
    static int count = 0;
    Serial.print("HitLeftRacket : ");
    Serial.println(count++);
  }
}

// STATE: Start
fader.loop();
int a = fader.getValue();
static char selectBulb = 2;
static int rnd_Speed = 1000;

CH[selectBulb] =   map(a, 0, 100, 60,0 );
usbMIDI.sendNoteOn(map(a, 0, 100, 70, 5),72,5);

// STATE: Complete

if(fader.isComplete())
{
  rnd_Speed = random(500,1000);
 // Serial.println(rnd_Speed);

  fader.setSpeed(rnd_Speed);
  fader.restart();
  selectBulb = char(random(0,8));
}



}