//*******************************************************************
/*!
\file   sensorTOF.cpp
\author Thomas Breuer (Bonn-Rhein-Sieg University of Applied Sciences)
\date   03.02.2021
*/

//*******************************************************************
#include "lib.h"
#include "SensorTOF.h"

//*******************************************************************
#if (system_PCLK_TIM == 84000000)
// 84 MHz, 60000µs => ps = 100, tics 25200,
#define TIME_PER_TIC (100.0/84.0) // 100/42 µs
#endif
//*******************************************************************
//
// SensorTOF::ExtIntHandler
//
//*******************************************************************
//*******************************************************************
SensorTOF::ExtIntHandler::ExtIntHandler( cHwExtInt &extInt,
                                         SensorTOF &sensor )
: sensor( sensor )
{
  extInt.add(this);
}

//*******************************************************************
void SensorTOF::ExtIntHandler::update()
{
  if( sensor.isEnable )
  {
    // interrupt disable
    if( sensor.isStarted )
    {
      // TODO: Direkten Zugrif auf TIM10 vermeiden
      sensor.cnt = TIM10->CNT; /// hacked !!!
      sensor.isStarted = false;
      sensor.extInt.setEdge( cHwExtInt::FALLING);
    }
    else
    {
      sensor.result = TIME_PER_TIC*( TIM10->CNT - sensor.cnt );
      sensor.extInt.setEdge( cHwExtInt::NONE);
    }
    //interrupt enable
  }
}

//*******************************************************************
SensorTOF::TimerHandler::TimerHandler( SensorTOF &sensor )
: sensor( sensor )
{
  sensor.tim.add(this);
}

//*******************************************************************
void SensorTOF::TimerHandler::update()
{
  if( sensor.isEnable )
  {
    System::disableInterrupt();// interrupt disable
    if(sensor.isStarted  ) // keine Antwort
    {
      sensor.result = 30000;
      sensor.isStarted = false;
      sensor.extInt.setEdge(cHwExtInt::NONE);
    }


    sensor.context.digitalB.set(1);
    sensor.context.digitalB.setMode(Port::OutPU);

    sensor.context.digitalC.set(0);

    System::delayMicroSec(10);
    // interrupt enable
    sensor.context.digitalC.set(0);
    sensor.context.digitalB.setMode(Port::In);

    //  sensor->digitalA.set(0);

    sensor.extInt.setEdge(cHwExtInt::RISING);
    sensor.isStarted = true;
    System::enableInterrupt();
    // interrupt disable
  }
}

//*******************************************************************
//
// SensorTOF
//
//*******************************************************************
//-------------------------------------------------------------------
SensorTOF::SensorTOF( Sensor::Context &context,
                      Timer        &tim,
                      cHwExtInt       &extInt )

: Sensor  ( context       ),
  tim     ( tim           ),
  extInt  ( extInt        ),
  tHandler(         *this ),
  eHandler( extInt, *this )

{
  isEnable  = false;
  isStarted = false;
}

//-------------------------------------------------------------------
void SensorTOF::start( void )
{
  report.reset( cConfigToORB::Data::SensorConfig::TOF );

  context.digitalA.setMode( Port::In );
  context.digitalB.setMode( Port::In );

  /// digitalC.setMode( cHwPort::InPU );

  context.digitalC.setMode( Port::OutPP );

  context.digitalA.set( 0 );
  context.digitalB.set( 0 );
  context.digitalC.set( 0 );

  isEnable = true;

  extInt.enable();
}

//-------------------------------------------------------------------
void SensorTOF::stop( void )
{
  isEnable = false;
  extInt.disable();

  context.digitalA.setMode( Port::InPU );
  context.digitalB.setMode( Port::InPU );

  // TODO: reset Pin 2 / digitalC back to analog input
  context.digitalC.setMode( Port::In );

  context.digitalA.set();
  context.digitalB.set();
}

//-------------------------------------------------------------------
void SensorTOF::update( void )
{
  report.rep.value[0] = result;
  report.setValid();
}

//-------------------------------------------------------------------
bool SensorTOF::configMode( BYTE mode, WORD option )
{
  context.digitalA.set( mode );
  return true;
}

//EOF
