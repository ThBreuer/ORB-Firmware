//*******************************************************************
/*!
\file   SensorTouch.h
\author Thomas Breuer (Bonn-Rhein-Sieg University of Applied Sciences)
\date   03.02.2021
*/

//*******************************************************************
#ifndef _SENSOR_TOUCH_H
#define _SENSOR_TOUCH_H

//*******************************************************************
#include "Sensor.h"

//*******************************************************************
/*!
\class SensorTouch
\brief
*/
class SensorTouch : public Sensor
{
  public:
    //---------------------------------------------------------------
    SensorTouch( Sensor::Context &context );

  private:
    //---------------------------------------------------------------
    virtual void start( void );

    //---------------------------------------------------------------
    virtual void stop( void );

    //---------------------------------------------------------------
    virtual void update( void );

    //---------------------------------------------------------------
    virtual bool configMode( BYTE mode, WORD optionIn );

};

#endif
