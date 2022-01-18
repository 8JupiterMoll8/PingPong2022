#include <Arduino.h>
#include <SPI.h>
#include "printf.h"
#include "RF24.h"
#include "Reciver.hpp"
#include "ReciverData.hpp"
#include "PeaKDetector.hpp"


/*
██████╗ ███████╗██████╗ ██╗  ██╗
██╔══██╗██╔════╝╚════██╗██║  ██║
██████╔╝█████╗   █████╔╝███████║
██╔══██╗██╔══╝  ██╔═══╝ ╚════██║
██║  ██║██║     ███████╗     ██║
╚═╝  ╚═╝╚═╝     ╚══════╝     ╚═╝
*/

RF24                   radio(21, 20); //CE pin, CSN pin
const uint64_t ADRESS  {0xF0F0F0F0E1LL};
const byte     CHANNEl {125};               
ReciverData racketData;
Reciver reciver(radio, ADRESS, CHANNEL, racketData);

PeakDetector racketPiezo(racketData.pz);



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
  reciver.loop();
  racketPiezo.loop();
  //racketPiezo.getPeak();
  //racketPiezo

}