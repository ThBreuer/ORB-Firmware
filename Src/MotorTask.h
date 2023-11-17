//*******************************************************************
/*!
\file   MotorTask.h
\author Thomas Breuer (Bonn-Rhein-Sieg University of Applied Sciences)
\date   03.02.2021
*/

//*******************************************************************
#ifndef _MOTOR_TASK_H
#define _MOTOR_TASK_H

//*******************************************************************
#include "Motor.h"

//*******************************************************************
/*!
\class MotorTask
\brief
*/
class MotorTask : public TaskManager::Task
{
  public:
    //---------------------------------------------------------------
    MotorTask( TaskManager  &taskHandler,
               cDevMotor     &motorIn,
               cHwEncoder    &encoder );

    //---------------------------------------------------------------
    void set( BYTE modeIn,
              int  speedIn,
              int  posIn );

    void config( WORD ticsPerRotation,
                 BYTE acceleration,
                 BYTE Regler_Kp,
                 BYTE Regler_Ki );

    //---------------------------------------------------------------
    void get( ORB::Motor  &report );

  private:
    //---------------------------------------------------------------
    virtual void update( void);

  private:
    //---------------------------------------------------------------
    Motor motor;

};

#endif
