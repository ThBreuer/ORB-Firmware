//*******************************************************************
/*!
\file   SensorDebug.cpp
\author Thomas Breuer (Bonn-Rhein-Sieg University of Applied Sciences)
\date   03.02.2021
*/

//*******************************************************************
#include "lib.h"
#include "Module/Rtos/Rtos.h"

//*******************************************************************
#include "SensorDebug.h"

//*******************************************************************
//
// SensorDebug
//
//*******************************************************************
//-------------------------------------------------------------------
SensorDebug::SensorDebug( Sensor::Context &context )

  : Sensor( context )
{
  mode    = 0;
}

//-------------------------------------------------------------------
void SensorDebug::start( void )
{
  report.reset( cConfigToORB::Data::SensorConfig::DEBUG );
  cnt = 0;
}

//-------------------------------------------------------------------
void SensorDebug::stop( void )
{
}

//-------------------------------------------------------------------
void SensorDebug::update( void )
{
  report.reset( cConfigToORB::Data::SensorConfig::DEBUG );

  report.rep.lenExp = mode&0x07;

  ////  for(DWORD n=0;n<(1<<(report.lenExp-2));n++)
  ////    report.value[n] = (n<<24) | ((cnt++)&0x000FFFFF);

  report.rep.value[0] = 0xA0000000 | cnt++;
  report.rep.value[1] = 0xB0000000 | cnt++;

  report.setValid();
  report.rep.option = mode;

}

//-------------------------------------------------------------------
bool SensorDebug::configMode( BYTE mode, WORD option )
{
  this->mode = mode;
  this->option = option;

  return( true );
}

//EOF
