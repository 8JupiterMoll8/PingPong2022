#ifndef RACKETRIGHT_H
#define RACKETRIGHT_H
#pragma once
#include "Piezo.hpp"
#include "Speed.hpp"
#include "Swing.hpp"
#include "Mahony.hpp"
#include "Pressure.hpp" 
class RacketRight
{
private:
	//Hit Behaviour
	Piezo &m_piezo;
	//Motion Behaviour
	Speed &m_speed;
	Swing &m_swing;
	Mahony &m_mahony;
	//Button Behaviour
	Pressure &m_pressure;



public:
	RacketRight(Piezo &piezo,  Speed &speed, Swing &swing, Mahony &mahony, Pressure &pressure): 
	m_piezo(piezo),
    m_speed(speed),
	m_swing(swing),
	m_mahony(mahony),
    m_pressure(pressure)
	{
		
	}
	

	void loop()
	{
     	m_piezo.loop();
		m_swing.loop();
		m_speed.loop();
		m_mahony.loop();
		m_pressure.loop();
	}

	//SPEED
	float speed(){ return m_speed.getNormal();};
	//SWING
	float swing_A_Gain() { return m_swing.A_Gain();}
	float swing_B_Gain() { return m_swing.B_Gain();}
	//HIT
	boolean isHit() { return m_piezo.isHit();}
	int hitSum()    { return m_piezo.hitSum();}
	void resetHitSum(){ m_piezo.resetHitSum();}
	//ROLL PITCH YAW
	float roll()  { return m_mahony.roll(); }
	float pitch() { return m_mahony.pitch();}
	float yaw()   { return m_mahony.yaw();}
	//PRESSURE BUTTON
	int pressure(){ return m_pressure.value();}
	
};
#endif