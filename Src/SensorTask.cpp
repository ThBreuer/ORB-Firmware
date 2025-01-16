//*******************************************************************
/*!
\file   SensorTask.cpp
\author Thomas Breuer (Bonn-Rhein-Sieg University of Applied Sciences)
\date   03.02.2021
*/

//*******************************************************************
#include "lib.h"
#include "Module/Rtos/Rtos.h"

//*******************************************************************
#include "SensorTask.h"
#include "Common/Properties.h"

//*******************************************************************
//
// SensorTask
//
//*******************************************************************
//-------------------------------------------------------------------
SensorTask::SensorTask( Rtos           &rtosIn,
                        Sensor::Context &context,
                        cHwUART_Ext     &sIn,
                        Timer        &tim,
                        cHwExtInt       &extInt )

: Rtos::Task ( rtosIn, 0x500       ),
  sensorAnalog( context             ),
  sensorUART  ( context, sIn        ),
  sensorI2C   ( context             ),
  sensorTOF   ( context, tim, extInt),
  sensorTouch ( context             ),
  sensorDebug ( context             )

{
  sensor    = &sensorAnalog;
  type      = cConfigToORB::Data::SensorConfig::ANALOG;
  mode      = 0;
  option    = 0;
  isNewType = false;
  isNewMode = false;

  start(); // Start this RTOS-Task
}

//-------------------------------------------------------------------
void SensorTask::update( void )
{
  sensor->start();

  while(1)
  {
    if( isNewType )
    {
      switch( type )
      {
        default:
        case cConfigToORB::Data::SensorConfig::ANALOG: sensor = &sensorAnalog; break;
        case cConfigToORB::Data::SensorConfig::UART:   sensor = &sensorUART;   break;
        case cConfigToORB::Data::SensorConfig::I2C:    sensor = &sensorI2C;    break;
        case cConfigToORB::Data::SensorConfig::TOF:    sensor = &sensorTOF;    break;
        case cConfigToORB::Data::SensorConfig::TOUCH:  sensor = &sensorTouch;  break;
        case cConfigToORB::Data::SensorConfig::DEBUG:  sensor = &sensorDebug;  break;
      }
      sensor->start();
      isNewType = false;
    }

    if( isNewMode && sensor->configMode( mode, option ) )
    {
      isNewMode = false;
    }

    sensor->update();

    reportBuffer << sensor->report.rep;
  }
}

//-------------------------------------------------------------------
void SensorTask::config( BYTE typeIn,
                         BYTE modeIn,
                         WORD optionIn )
{
  if( type != typeIn )
  {
    type      = typeIn;
    mode      = modeIn;
    option    = optionIn;
    isNewType = true;
    isNewMode = true;
  }
  else if( mode != modeIn || option != optionIn)
  {
    mode      = modeIn;
    option    = optionIn;
    isNewMode = true;
  }
}

//-------------------------------------------------------------------
void SensorTask::get( ORB::Sensor &report )
{
  reportBuffer >> report;
}

//EOF
