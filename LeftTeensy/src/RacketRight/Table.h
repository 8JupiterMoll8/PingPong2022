#ifndef TABLE_H
#define TABLE_H

#pragma once
#include "Piezo.hpp"
class Table
{
private:
Piezo &m_piezo;
public:
    Table(Piezo &piezo):m_piezo(piezo)
    {

    }

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