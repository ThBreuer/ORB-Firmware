//*******************************************************************
/*!
\file   SensorI2C_NXTultraschall.h
\author Thomas Breuer (Bonn-Rhein-Sieg University of Applied Sciences)
\date   03.02.2021
*/

//*******************************************************************
#ifndef _SENSOR_I2C_NXT_ULTRASCHALL_H
#define _SENSOR_I2C_NXT_ULTRASCHALL_H

//*******************************************************************
#include "SensorI2C_Strategy.h"

//*******************************************************************
/*!
\class SensorI2C_NXTultraschall
\brief
*/
class SensorI2C_NXTultraschall : public SensorI2C_Strategy
{
  public:
    //---------------------------------------------------------------
    SensorI2C_NXTultraschall( SensorI2C &sensorIn );

  private:
    //---------------------------------------------------------------
    virtual void start( BYTE option );

    //---------------------------------------------------------------
    virtual void stop( void );

    //---------------------------------------------------------------
    virtual void update( void );

    //I2Cmaster_Emul     i2c;
    I2Cmaster::Device  us;

};

#endif
