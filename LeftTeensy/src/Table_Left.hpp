#ifndef TABLE_LEFT_H
#define TABLE_LEFT_H
#pragma once
#include "Table.hpp"

class Table_Left : public Table
{
private:
public:
	Table_Left()
	{

	}
	void setup()
	{
		m_peakDetecor.setAfterSchockMillis()
	    m_peakDetecor.setThersholdMin(35);
		m_peakDetecor.setPeakTrackMillis(10);
		m_peakDetecor.setAfterSchockMillis(25);
	}

	void loop()
	{
		m_peakDetecor.loop();
	}
};
#endif