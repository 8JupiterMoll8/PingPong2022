#ifndef SPEED_H
#define SPEED_H
#pragma once
#include "ReciverData.hpp"
//! This is a concrete class, for getting 
class Speed
{
private:
	ReciverData &m_reciverData;
	float &m_speed;
	float &m_speedSmooth;
	float m_smoothSensitivity = 100;

public:
	Speed(ReaciverData &reciverData) : m_reciverData(reciverData){

									   };

	void loop()
	{
		calculateTotalSpeed();
		smoothTotalSpeed();
	}

	float smooth()
	{
		return m_speedSmooth

	}

	int setSmoothSensivity(int smoothSensivity)
	{
		m_smoothSensitivity = smoothSensivity;
	}

	float normal()
	{
		return m_speed ;

	}

private:                   
	void smoothTotalSpeed()
	{
		float sensitivity = 100; // a total of 540 degrees per second or greater between all axes will apply the loudest swing sound
		m_speedSmooth= min(1.0f, calculateTotalSpeed() / sensitivity);
		
	}

 

	float calculateTotalSpeed()
	{
		m_speed = sqrtf(powf(m_reciverData.gx, 2) + powf(m_reciverData.gy, 2) + powf(m_reciverData.gz, 2));
		return m_speed;

	}
};
#endif

