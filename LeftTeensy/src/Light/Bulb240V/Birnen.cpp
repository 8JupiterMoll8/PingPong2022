#include "Birnen.hpp"
     unsigned char Birnen:: clock_tick =0;

	unsigned char Birnen:: channel_1 = 3;  // Output to Opto Triac pin, channel 1
	unsigned char Birnen:: channel_2 = 4;  // Output to Opto Triac pin, channel 2
	unsigned char Birnen:: channel_3 = 5;  // Output to Opto Triac pin, channel 3
	unsigned char Birnen:: channel_4 = 6;  // Output to Opto Triac pin, channel 4
	unsigned char Birnen:: channel_5 = 7;  // Output to Opto Triac pin, channel 5
	unsigned char Birnen:: channel_6 = 8;  // Output to Opto Triac pin, channel 6
	unsigned char Birnen:: channel_7 = 9;  // Output to Opto Triac pin, channel 7
	unsigned char Birnen:: channel_8 = 10; // Output to Opto Triac pin, channel 8
	unsigned char Birnen:: CH1, CH2, CH3, CH4, CH5, CH6, CH7, CH8;
	unsigned char Birnen:: CHANNEL_SELECT;
	//unsigned cochar Birnen:: CH[8] = {CH1, CH2, CH3, CH4, CH5, CH6, CH7, CH8};