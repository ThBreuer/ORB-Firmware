//*******************************************************************
/*!
\file   SensorI2C_TCS3472.h
\author Thomas Breuer (Bonn-Rhein-Sieg University of Applied Sciences)
\date   03.02.2021
*/

//*******************************************************************
#ifndef _SENSOR_I2C_TCS3472_H
#define _SENSOR_I2C_TCS3472_H

//*******************************************************************
#include "SensorI2C_Strategy.h"

//*******************************************************************
/*!
\class SensorI2C_TCS3472
\brief
*/
class SensorI2C_TCS3472 : public SensorI2C_Strategy
{
  public:
    //---------------------------------------------------------------
    SensorI2C_TCS3472( SensorI2C &sensorIn );

  private:
    //---------------------------------------------------------------
    virtual void start( BYTE option );

    //---------------------------------------------------------------
    virtual void stop( void );

    //---------------------------------------------------------------
    virtual void update( void );

  private:
    //---------------------------------------------------------------
    I2Cmaster::Device  us;
};

#endif
