#include <Arduino.h>
#include <SPI.h>
#include "printf.h"
#include "RF24.h"
#include "Reciver.hpp"
#include "ReciverData.hpp"
#include "PeaKDetector.hpp"
#include "Racket.hpp"


/*
██████╗ ███████╗██████╗ ██╗  ██╗
██╔══██╗██╔════╝╚════██╗██║  ██║
██████╔╝█████╗   █████╔╝███████║
██╔══██╗██╔══╝  ██╔═══╝ ╚════██║
██║  ██║██║     ███████╗     ██║
╚═╝  ╚═╝╚═╝     ╚══════╝     ╚═╝
*/

RF24 radio(21, 20); //CE pin, CSN pin
const uint64_t ADRESS  {0xF0F0F0F0E1LL};
const byte CHANNEL {125};               
ReciverData racketData;
Reciver reciver(radio, ADRESS, CHANNEL, racketData);

//Racket
PeakDetector racketPiezo(racketData.pz);
Racket leftRacket(racketPiezo,racketData);

//Tablet
PeakDetector  tableLeftPiezos;
PeakDetector  tableRightPiezos;



void setup()
{
  Serial.begin(9600);
  while (!Serial)
  {
  }

  reciver.setup();
 
}

void loop()
{
  // The Reciver fetch constanly Data from the Transmitter
  // to be used by the objects, which depend on them
  reciver.loop();

  //Racket
  leftRacket.loop();

  //Table
  // tableRightPiezos.loop();
  // tableRightPiezos.loop();
  // tableLeftPiezos.setInput(analogRead(41));
  // tableRightPiezos.setInput(analogRead(40));
  Serial.println(analogRead(A17));
  delay(10);

  
  

}