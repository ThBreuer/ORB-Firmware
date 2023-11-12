//*******************************************************************
/*!
\file   SensorTask.h
\author Thomas Breuer (Bonn-Rhein-Sieg University of Applied Sciences)
\date   03.02.2021
*/

//*******************************************************************
#ifndef _SENSOR_TASK_H
#define _SENSOR_TASK_H

//*******************************************************************
#include "lib.h"
#include "Module/Rtos/Rtos.h"

#include "Sensor.h"
#include "SensorUART.h"
#include "SensorI2C.h"
#include "SensorAnalog.h"
#include "SensorTOF.h"
#include "SensorTouch.h"
#include "SensorDebug.h"

//*******************************************************************
/*!
\class SensorTask
\brief
*/
class SensorTask : public Rtos::Task
{
  public:
    //---------------------------------------------------------------
    SensorTask( Rtos           &rtosIn,
                Sensor::Context &context,
                cHwUART_Ext     &sIn,
                Timer        &tim ,
                cHwExtInt       &extInt);

    //---------------------------------------------------------------
    virtual void config( BYTE type,
                         BYTE mode,
                         WORD option = 0 );

    //---------------------------------------------------------------
    virtual void get( ORB::Sensor &report );

  private:
    //---------------------------------------------------------------
    virtual void update( void );

  private:
    //---------------------------------------------------------------
    cSharedMem<ORB::Sensor>  reportBuffer;

    SensorAnalog  sensorAnalog;
    SensorUART    sensorUART;
    SensorI2C     sensorI2C;
    SensorTOF     sensorTOF;
    SensorTouch   sensorTouch;
    SensorDebug   sensorDebug;

  public:
    //---------------------------------------------------------------
    Sensor       *sensor;

  private:
    //---------------------------------------------------------------
    BYTE          type;
    BYTE          mode;
    WORD          option;
    BYTE          isNewType;
    BYTE          isNewMode;

};
#endif
