//*******************************************************************
/*!
\file   SensorAnalog.h
\author Thomas Breuer (Bonn-Rhein-Sieg University of Applied Sciences)
\date   03.02.2021
*/

//*******************************************************************
#ifndef _SENSOR_ANALOG_H
#define _SENSOR_ANALOG_H

//*******************************************************************
#include "Sensor.h"

//*******************************************************************
/*!
\class
\brief
*/
class SensorAnalog : public Sensor
{
  public:
    //---------------------------------------------------------------
    SensorAnalog( Sensor::Context &context );

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

    //---------------------------------------------------------------
    void setPinMode( Port::Pin &pin, BYTE mode );
};

#endif
