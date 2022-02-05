#ifndef RACKETLEFT_H
#define RACKETLEFT_H
#pragma once
#include "Piezo.hpp"

class RacketLeft
{
private:
Piezo &m_piezo;

public:
    RacketLeft(Piezo &piezo):m_piezo(piezo)
    {}

    void loop()
    {
        m_piezo.loop();

    }

    boolean isHit()
	{
		return m_piezo.isHit();
	}
	int hitSum()
	{
		return m_piezo.hitSum();
	}

	void resetHitSum()
	{
		m_piezo.resetHitSum();

	}
 


};

#endif