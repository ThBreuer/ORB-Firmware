//*******************************************************************
/*!
\file   SensorI2C.h
\author Thomas Breuer (Bonn-Rhein-Sieg University of Applied Sciences)
\date   03.02.2021
*/

//*******************************************************************
#ifndef _SENSOR_I2C_H
#define _SENSOR_I2C_H
#include "Sensor.h"
#include "SensorI2C/SensorI2C_NXTultraschall.h"
#include "SensorI2C/SensorI2C_TCS3472.h"
#include "SensorI2C/SensorI2C_VL53L0X.h"

//*******************************************************************
/*!
\class SensorI2C
\brief
*/
class SensorI2C : public Sensor
{
  public:
    //---------------------------------------------------------------
    SensorI2C( Sensor::Context &context );

  private:
    //---------------------------------------------------------------
    virtual void start( void );

    //---------------------------------------------------------------
    virtual void stop( void );

    //---------------------------------------------------------------
    virtual void update( void );

    //---------------------------------------------------------------
    virtual bool configMode( BYTE mode, WORD optionIn );

    //---------------------------------------------------------------
    virtual BYTE getCurrentMode(  ) {return(0);}

  public:
    //---------------------------------------------------------------
    Port::Pin         &scl;
    Port::Pin         &sda;
    I2Cmaster_Emul     i2c;

  private:
    //---------------------------------------------------------------
    SensorI2C_Strategy          *strategyPtr;
    SensorI2C_NXTultraschall     NXTultraschall;
    SensorI2C_TCS3472            TCS3472;
    SensorI2C_VL53L0X            VL53L0X;

};

#endif
