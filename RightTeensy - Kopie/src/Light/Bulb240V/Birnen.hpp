#ifndef BIRNEN_H
#define BIRNEN_H
#pragma once
#include <TimerOne.h>
#include "Arduino.h"

elapsedMillis ms;

void zero_crosss_int();
void timerIsr();
unsigned char channel_1 = 3;  // Output to Opto Triac pin, channel 1
unsigned char channel_2 = 4;  // Output to Opto Triac pin, channel 2
unsigned char channel_3 = 5;  // Output to Opto Triac pin, channel 3
unsigned char channel_4 = 6;  // Output to Opto Triac pin, channel 4
unsigned char channel_5 = 7;  // Output to Opto Triac pin, channel 5
unsigned char channel_6 = 8;  // Output to Opto Triac pin, channel 6
unsigned char channel_7 = 9; // Output to Opto Triac pin, channel 7
unsigned char channel_8 = 10; // Output to Opto Triac pin, channel 8
unsigned char CH1, CH2, CH3, CH4, CH5, CH6, CH7, CH8;
unsigned char CHANNEL_SELECT;
unsigned char i=0;
unsigned char clock_tick; // variable for Timer1
unsigned int delay_time = 150;

unsigned char low = 70;
unsigned char high = 5;

unsigned char CH[8]={CH1,CH2,CH3,CH4,CH5,CH6,CH7,CH8};


void setup_Dimmer()
{
  //CH1=CH2=CH3=CH4=CH5=CH6=CH7=CH8=95;

  pinMode(channel_1, OUTPUT);// Set AC Load pin as output
  pinMode(channel_2, OUTPUT);// Set AC Load pin as output
  pinMode(channel_3, OUTPUT);// Set AC Load pin as output
  pinMode(channel_4, OUTPUT);// Set AC Load pin as output
  pinMode(channel_5, OUTPUT);// Set AC Load pin as output
  pinMode(channel_6, OUTPUT);// Set AC Load pin as output
  pinMode(channel_7, OUTPUT);// Set AC Load pin as output
  pinMode(channel_8, OUTPUT);// Set AC Load pin as output
  pinMode(2, INPUT_PULLUP);
  attachInterrupt(2, zero_crosss_int, FALLING);
  Timer1.initialize(100); // set a timer of length 100 microseconds for 50Hz or 83 microseconds for 60Hz;
  Timer1.attachInterrupt( timerIsr ); // attach the service routine here


}

void timerIsr()
{
  clock_tick++;

  if (CH[0] == clock_tick)
  {
    digitalWrite(channel_1, HIGH); // triac firing
    delayMicroseconds(5); // triac On propogation delay (for 60Hz use 8.33)
    digitalWrite(channel_1, LOW); // triac Off
  }

  if (CH[1] == clock_tick)
  {
    digitalWrite(channel_2, HIGH); // triac firing
    delayMicroseconds(5); // triac On propogation delay (for 60Hz use 8.33)
    digitalWrite(channel_2, LOW); // triac Off
  }

  if (CH[2]  == clock_tick)
  {
    digitalWrite(channel_3, HIGH); // triac firing
    delayMicroseconds(5); // triac On propogation delay (for 60Hz use 8.33)
    digitalWrite(channel_3, LOW); // triac Off
  }

  if (CH[3]  == clock_tick)
  {
    digitalWrite(channel_4, HIGH); // triac firing
    delayMicroseconds(5); // triac On propogation delay (for 60Hz use 8.33)
    digitalWrite(channel_4, LOW); // triac Off
  }

  if (CH[4]  == clock_tick)
  {
    digitalWrite(channel_5, HIGH); // triac firing
    delayMicroseconds(5); // triac On propogation delay (for 60Hz use 8.33)
    digitalWrite(channel_5, LOW); // triac Off
  }

  if (CH[5]  == clock_tick)
  {
    digitalWrite(channel_6, HIGH); // triac firing
    delayMicroseconds(5); // triac On propogation delay (for 60Hz use 8.33)
    digitalWrite(channel_6, LOW); // triac Off
  }

  if (CH[6]  == clock_tick)
  {
    digitalWrite(channel_7, HIGH); // triac firing
    delayMicroseconds(5); // triac On propogation delay (for 60Hz use 8.33)
    digitalWrite(channel_7, LOW); // triac Off
  }

  if (CH[7]  == clock_tick)
  {
    digitalWrite(channel_8, HIGH); // triac firing
    delayMicroseconds(5); // triac On propogation delay (for 60Hz use 8.33)
    digitalWrite(channel_8, LOW); // triac Off
  }


}



void zero_crosss_int() // function to be fired at the zero crossing to dim the light
{
  // Every zerocrossing interrupt: For 50Hz (1/2 Cycle) => 10ms ; For 60Hz (1/2 Cycle) => 8.33ms
  // 10ms=10000us , 8.33ms=8330us

  clock_tick = 0;
}
#endif