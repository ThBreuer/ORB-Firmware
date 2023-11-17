//*******************************************************************
/*!
\file   SensorI2C_Strategy.h
\author Thomas Breuer (Bonn-Rhein-Sieg University of Applied Sciences)
\date   03.02.2021
*/

//*******************************************************************
#ifndef _SENSOR_I2C_STRATEGY_H
#define _SENSOR_I2C_STRATEGY_H

//*******************************************************************
class SensorI2C;

//*******************************************************************
/*!
\class SensorI2C_Strategy
\brief
*/
class SensorI2C_Strategy
{
  public:
    //-----------------------------------------------------------
    SensorI2C_Strategy( SensorI2C &sensor )

    : sensor( sensor )

    {
    }

    //-----------------------------------------------------------
    virtual void start( BYTE option ) = 0;

    //-----------------------------------------------------------
    virtual void stop( void ) = 0;

    //-----------------------------------------------------------
    virtual void update( void ) = 0;

  protected:
    //-----------------------------------------------------------
    SensorI2C &sensor;
};

#endif
