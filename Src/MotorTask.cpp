//*******************************************************************
/*!
\file   MotorTask.cpp
\author Thomas Breuer (Bonn-Rhein-Sieg University of Applied Sciences)
\date   03.02.2021
*/

//*******************************************************************
#include "lib.h"
#include "math.h"

//*******************************************************************
#include "MotorTask.h"
#include "Properties.h"

//*******************************************************************
//
// MotorTask
//
//*******************************************************************
//-------------------------------------------------------------------
MotorTask::MotorTask( TaskManager  &taskHandler,
                      cDevMotor     &motorIn,
                      cHwEncoder    &encoder )

: motor             ( motorIn,
                      encoder )

{
    taskHandler.add( this );
}

//-------------------------------------------------------------------
void MotorTask::update( void )
{
  motor.update();
}

//-------------------------------------------------------------------
void MotorTask::set( BYTE modeIn, int speedIn, int  posIn )
{
  Motor::Setting setting;

  switch( modeIn )
  {
    default:
      setting.mode  = Motor::FREE;
      setting.speed = 0;
      setting.pos   = 0;
      break;

    case cPropToORB::Data::Motor::POWER_MODE:
      setting.mode  = Motor::FREE;
      setting.speed = speedIn;
      setting.pos   = 0;
      break;

    case cPropToORB::Data::Motor::BRAKE_MODE:
      setting.mode  = Motor::BRAKE;
      setting.speed = 0;
      setting.pos   = 0;
      break;

    case cPropToORB::Data::Motor::SPEED_MODE:
      setting.mode  = Motor::SPEED;
      setting.speed = 0.001*(float)speedIn;
      setting.pos   = 0;
      break;

    case cPropToORB::Data::Motor::MOVETO_MODE:
      setting.mode  = Motor::POSITION;
      setting.speed = ::fabs(0.001*(float)speedIn);
      setting.pos   = posIn;
      break;
  }

  motor.settingBuffer << setting;
}

//-------------------------------------------------------------------
void MotorTask::config( WORD ticsPerRotation,
                        BYTE acceleration,
                        BYTE Regler_Kp,
                        BYTE Regler_Ki )
{
  Motor::Config config;

  if( ticsPerRotation < 1)
    return;

  config.ticsToRot =  100.0 /  (float)ticsPerRotation;
  config.Regler_Kp =   10.0   *(float)Regler_Kp;
  config.Regler_Ki =    1.0   *(float)Regler_Ki;
  config.acc       =    5.0E-5*(float)acceleration;

  motor.configBuffer << config;
}


//-------------------------------------------------------------------
void MotorTask::get( ORB::Motor  &report )
{
  motor.reportBuffer >> report;
}
