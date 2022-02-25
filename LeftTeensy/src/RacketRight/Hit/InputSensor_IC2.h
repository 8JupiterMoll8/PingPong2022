#ifndef INPUTSENSOR_IC2_H
#define INPUTSENSOR_IC2_H

#pragma once
#include "I_InputSensorBhv.hpp"
#include "ReciverData_IC2.h"

class InputSensor_IC2: public I_InputSensorBhv
{
private:
 TransmitData  &m_data_ic2;
public:
    InputSensor_IC2( TransmitData &data_IC2):
    m_data_ic2(data_IC2)
    {

    }

       virtual void loop() override
		{
			//not used
			

		}

		virtual int getValue () override
		{
		return	m_data_ic2.pz;
		}	
  




};

#endif