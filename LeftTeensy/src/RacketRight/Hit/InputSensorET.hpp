#ifndef INPUTSENSORET_H
#define INPUTSENSORET_H
#pragma once
#include "I_InputSensorBhv.hpp"
#include "ReciverDataET.hpp"
	
class InputSensorET  : public I_InputSensorBhv
{
	private:
	RECEIVE_DATA_STRUCTURE &m_recive_data_structure;

	public:

		InputSensorET(RECEIVE_DATA_STRUCTURE &recive_data_structure):
		m_recive_data_structure(recive_data_structure)
		{

		}

		virtual void loop() override
		{
			//not used
			

		}

		virtual int getValue () override
		{
		return	m_recive_data_structure.pz;
		}	

		

};
#endif