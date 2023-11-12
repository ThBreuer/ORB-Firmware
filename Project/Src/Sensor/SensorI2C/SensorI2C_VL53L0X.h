//*******************************************************************
/*!
\file   SensorI2C_VL53L0X.h
\author Thomas Breuer (Bonn-Rhein-Sieg University of Applied Sciences)
\date   03.02.2021
*/

//*******************************************************************
#ifndef _SENSOR_I2C_VL53L0X_DISTANCE_H
#define _SENSOR_I2C_VL53L0X_DISTANCE_H

//*******************************************************************
#include "SensorI2C_Strategy.h"
#include "VL53L0X.h"

//*******************************************************************
/*!
\class SensorI2C_VL53L0X
\brief
*/
class SensorI2C_VL53L0X : public SensorI2C_Strategy
{
  public:
    //---------------------------------------------------------------
    SensorI2C_VL53L0X( SensorI2C &sensor );

  private:
    //---------------------------------------------------------------
    virtual void start( BYTE option );

    //---------------------------------------------------------------
    virtual void stop( void );

    //---------------------------------------------------------------
    virtual void update( void );

  private:
    //---------------------------------------------------------------
    Rtos::TimeOut t;
    Rtos::TimeOut t2;

    I2Cmaster_Emul i2c2;
    VL53L0X           s0;
    VL53L0X           s1;
    BYTE              isDoubleCh;

};

#endif
