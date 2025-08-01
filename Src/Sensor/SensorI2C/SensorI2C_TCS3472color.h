//*******************************************************************
/*!
\file   SensorI2C_TCS3472color.h
\author Thomas Breuer (Bonn-Rhein-Sieg University of Applied Sciences)
\date   23.05.2025
*/

//*******************************************************************
#ifndef _SENSOR_I2C_TCS3472_COLOR_H
#define _SENSOR_I2C_TCS3472_COLOR_H

//*******************************************************************
#include "SensorI2C_Strategy.h"

//*******************************************************************
/*!
\class SensorI2C_TCS3472color
\brief
*/
class SensorI2C_TCS3472color : public SensorI2C_Strategy
{
  private:
    //*******************************************************************
    class Data
    {
      public:
        WORD r;
        WORD g;
        WORD b;
    };

  public:
    //---------------------------------------------------------------
    SensorI2C_TCS3472color( SensorI2C &sensorIn );

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
