//*******************************************************************
/*!
\file   AppTask.h
\author Thomas Breuer (Bonn-Rhein-Sieg University of Applied Sciences)
\date   03.02.2021
*/

//*******************************************************************
#ifndef _APP_TASK_H
#define _APP_TASK_H

//*******************************************************************
#include "MotorTask.h"
#include "ServoTask.h"
#include "SensorTask.h"

#include "ORBlocal.h"
#include "MotorTask.h"
#include "SensorTask.h"

#include "Monitor.h"

//*******************************************************************
extern Memory_Flash  mem1;
//extern Memory_Flash  mem3_1;
//extern Memory_RAM    mem3_2;

//*******************************************************************
/*!
\class
\brief
*/
class AppTask : public Rtos::Task
{
  public:
    //---------------------------------------------------------------
    BYTE Parameter;

    static BYTE       MonitorEvent;
    static cORBlocal  orb;

  public:
    //---------------------------------------------------------------
    AppTask(Rtos &rtosIn);

    //---------------------------------------------------------------
    virtual ~AppTask();

    //---------------------------------------------------------------
    virtual void update( );

//    //---------------------------------------------------------------
//    virtual void OnStop(void);
//
//    //---------------------------------------------------------------
//    virtual void OnStart(void);

    //---------------------------------------------------------------
    void Start( BYTE para );

  public:
    //---------------------------------------------------------------
    static void configMotor(void * ptr, BYTE id, WORD t, BYTE a, BYTE Kp, BYTE Ki);

    //---------------------------------------------------------------
    static void setMotor(void * ptr, BYTE id, BYTE mode, short speed, int pos);

    //---------------------------------------------------------------
    static ORB::Motor getMotor(void *ptr, BYTE id);

    //---------------------------------------------------------------
    static void setModelServo(void *ptr, BYTE id,BYTE speed, BYTE winkel);

    //---------------------------------------------------------------
    static void configSensor(void * ptr, BYTE id, BYTE type, BYTE mode, WORD option );

    //---------------------------------------------------------------
    static ORB::Sensor getSensor(void *ptr, BYTE id);

    //---------------------------------------------------------------
    static WORD getSensorValueExt(void *ptr, BYTE id, BYTE ch);

    //---------------------------------------------------------------
    static BYTE getSensorDigital(void *ptr, BYTE id);

    //---------------------------------------------------------------
    static void setMonitorText(void *ptr, BYTE line,const char *format, va_list va);

    //---------------------------------------------------------------
    static int getMonitorKey(void *ptr );

    //---------------------------------------------------------------
    static DWORD getTime(void *ptr);

    //---------------------------------------------------------------
    static void wait(void *ptr, DWORD time);

    //---------------------------------------------------------------
    static void clearMemory(void *ptr);

    //---------------------------------------------------------------
    static void setMemory(void *ptr, DWORD addr, BYTE *data, DWORD size );

    //---------------------------------------------------------------
    static void getMemory(void *ptr, DWORD addr, BYTE *data, DWORD size );

};
#endif
