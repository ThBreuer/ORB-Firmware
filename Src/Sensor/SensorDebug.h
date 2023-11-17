//*******************************************************************
/*!
\file   SensorDebug.h
\author Thomas Breuer (Bonn-Rhein-Sieg University of Applied Sciences)
\date   03.02.2021
*/

//*******************************************************************
#ifndef _SENSOR_DEBUG_H
#define _SENSOR_DEBUG_H

//*******************************************************************
#include "Sensor.h"

//*******************************************************************
/*!
\class
\brief
*/
class SensorDebug : public Sensor
{
  public:
    //---------------------------------------------------------------

  public:
    //---------------------------------------------------------------
    BYTE mode;
    WORD option;
    BYTE buf[32];
    DWORD cnt;

  public:
    //---------------------------------------------------------------
    SensorDebug( Sensor::Context &context);

    //---------------------------------------------------------------
    virtual void start();

    //---------------------------------------------------------------
    virtual void stop( void );

    //---------------------------------------------------------------
    virtual void update( void );

    //---------------------------------------------------------------
    virtual bool configMode( BYTE mode, WORD option );

};

#endif
