//*******************************************************************
/*!
\file   SensorTOF.h
\author Thomas Breuer (Bonn-Rhein-Sieg University of Applied Sciences)
\date   03.02.2021
*/

//*******************************************************************
#ifndef _SENSOR_TOF_H
#define _SENSOR_TOF_H

//*******************************************************************
#include "Sensor.h"

//*******************************************************************
/*!
\class SensorTOF
\brief
*/
class SensorTOF : public Sensor
{
  private:
    //---------------------------------------------------------------
    class TimerHandler : public Timer::Task
    {
      public:
        TimerHandler( SensorTOF &sensor );
      private:
        void update();
      private:
        SensorTOF &sensor;
    };

  private:
    //---------------------------------------------------------------
    class ExtIntHandler : public cHwExtInt::Task
    {
      public:
        ExtIntHandler( cHwExtInt &extInt, SensorTOF &sensor );
      private:
        void update();
      private:
        SensorTOF &sensor;
    };

  public:
    //---------------------------------------------------------------
    SensorTOF( Sensor::Context &context,
               Timer        &tim,
               cHwExtInt       &extInt );

  private:
    //---------------------------------------------------------------
    virtual void start( void );

    //---------------------------------------------------------------
    virtual void stop( void );

    //---------------------------------------------------------------
    virtual void update( void );

    //---------------------------------------------------------------
    virtual bool configMode( BYTE mode, WORD option );

    //---------------------------------------------------------------
    virtual BYTE getCurrentMode( void ) {return(0);}


    Timer     &tim;
    cHwExtInt    &extInt;

    TimerHandler  tHandler;
    ExtIntHandler eHandler;

  private:
    //---------------------------------------------------------------
    BYTE   isEnable;
    DWORD  cnt;
    BYTE   isStarted;
    DWORD  result;

};
#endif
