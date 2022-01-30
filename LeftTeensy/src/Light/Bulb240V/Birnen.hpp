#ifndef BIRNEN_H
#define BIRNEN_H
#pragma once
#include <TimerOne.h>
#include "Arduino.h"

class Birnen
{
private:

	elapsedMillis ms;
	static unsigned char channel_1 ;  // Output to Opto Triac pin, channel 1
	static unsigned char channel_2 ;  // Output to Opto Triac pin, channel 2
	static unsigned char channel_3 ;  // Output to Opto Triac pin, channel 3
	static unsigned char channel_4 ;  // Output to Opto Triac pin, channel 4
	static unsigned char channel_5 ;  // Output to Opto Triac pin, channel 5
	static unsigned char channel_6 ;  // Output to Opto Triac pin, channel 6
	static unsigned char channel_7 ;  // Output to Opto Triac pin, channel 7
	static unsigned char channel_8 ; // Output to Opto Triac pin, channel 8
	static unsigned char CH1, CH2, CH3, CH4, CH5, CH6, CH7, CH8;
	static unsigned char CHANNEL_SELECT;
	unsigned char i = 0;
	static unsigned char clock_tick; // variable for Timer1
	unsigned int delay_time = 150;

	unsigned char low = 70;
	unsigned char high = 5;

	static unsigned char CH[8];

public:
	Birnen()
	{
	}

	void setup()
	{
		pinMode(channel_1, OUTPUT); // Set AC Load pin as output
		pinMode(channel_2, OUTPUT); // Set AC Load pin as output
		pinMode(channel_3, OUTPUT); // Set AC Load pin as output
		pinMode(channel_4, OUTPUT); // Set AC Load pin as output
		pinMode(channel_5, OUTPUT); // Set AC Load pin as output
		pinMode(channel_6, OUTPUT); // Set AC Load pin as output
		pinMode(channel_7, OUTPUT); // Set AC Load pin as output
		pinMode(channel_8, OUTPUT); // Set AC Load pin as output
		pinMode(2, INPUT_PULLUP);
		attachInterrupt(2, zero_crosss_int, FALLING);
		Timer1.initialize(100);			  // set a timer of length 100 microseconds for 50Hz or 83 microseconds for 60Hz;
		Timer1.attachInterrupt(timerIsr); // attach the service routine here
	}

	void loop()
	{
	}

	void setBrightnesAll(int brigntness)
	{
       CH1=CH2=CH3=CH4=CH5=CH6=CH7=CH8=brigntness;
	}



private:
    static void timerIsr()
	{
		clock_tick++;

		if (CH1 == clock_tick)
		{
			digitalWrite(channel_1, HIGH); // triac firing
			delayMicroseconds(5);		   // triac On propogation delay (for 60Hz use 8.33)
			digitalWrite(channel_1, LOW);  // triac Off
		}

		if (CH2 == clock_tick)
		{
			digitalWrite(channel_2, HIGH); // triac firing
			delayMicroseconds(5);		   // triac On propogation delay (for 60Hz use 8.33)
			digitalWrite(channel_2, LOW);  // triac Off
		}

		if (CH3 == clock_tick)
		{
			digitalWrite(channel_3, HIGH); // triac firing
			delayMicroseconds(5);		   // triac On propogation delay (for 60Hz use 8.33)
			digitalWrite(channel_3, LOW);  // triac Off
		}

		if (CH4 == clock_tick)
		{
			digitalWrite(channel_4, HIGH); // triac firing
			delayMicroseconds(5);		   // triac On propogation delay (for 60Hz use 8.33)
			digitalWrite(channel_4, LOW);  // triac Off
		}

		if (CH5 == clock_tick)
		{
			digitalWrite(channel_5, HIGH); // triac firing
			delayMicroseconds(5);		   // triac On propogation delay (for 60Hz use 8.33)
			digitalWrite(channel_5, LOW);  // triac Off
		}

		if (CH6 == clock_tick)
		{
			digitalWrite(channel_6, HIGH); // triac firing
			delayMicroseconds(5);		   // triac On propogation delay (for 60Hz use 8.33)
			digitalWrite(channel_6, LOW);  // triac Off
		}

		if (CH7 == clock_tick)
		{
			digitalWrite(channel_7, HIGH); // triac firing
			delayMicroseconds(5);		   // triac On propogation delay (for 60Hz use 8.33)
			digitalWrite(channel_7, LOW);  // triac Off
		}

		if (CH8 == clock_tick)
		{
			digitalWrite(channel_8, HIGH); // triac firing
			delayMicroseconds(5);		   // triac On propogation delay (for 60Hz use 8.33)
			digitalWrite(channel_8, LOW);  // triac Off
		}
	}

	static void zero_crosss_int() // function to be fired at the zero crossing to dim the light
	{
		// Every zerocrossing interrupt: For 50Hz (1/2 Cycle) => 10ms ; For 60Hz (1/2 Cycle) => 8.33ms
		// 10ms=10000us , 8.33ms=8330us

		clock_tick = 0;
	}
};
#endif