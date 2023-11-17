//*******************************************************************
/*!
\file   SensorI2C.cpp
\author Thomas Breuer (Bonn-Rhein-Sieg University of Applied Sciences)
\date   03.02.2021
*/

//*******************************************************************
#include "lib.h"
#include "Module/Rtos/Rtos.h"

//*******************************************************************
#include "SensorI2C.h"

//*******************************************************************
//
// SensorI2C
//
//*******************************************************************
//-------------------------------------------------------------------
SensorI2C::SensorI2C( Sensor::Context &context )

: Sensor( context ),
  scl( context.digitalA ),
  sda( context.digitalB ),

  i2c( scl, sda, 10 ),
  //  i2c2(context.digitalD,context.digitalC,cHwI2Cmaster::CR_400kHz),

  NXTultraschall( *this )

{
  strategyPtr = NULL;
}

//-------------------------------------------------------------------
void SensorI2C::start( void )
{
  report.reset( cConfigToORB::Data::SensorConfig::I2C );

  scl.set( );
  sda.set( );
  scl.setMode( Port::OutPU );
  sda.setMode( Port::OutPU );

}

//-------------------------------------------------------------------
void SensorI2C::stop( void )
{
  if( strategyPtr )
  {
    strategyPtr->stop();
  }
  scl.set();
  sda.set();

  scl.setMode( Port::InPU );
  sda.setMode( Port::InPU );
}

//-------------------------------------------------------------------
void SensorI2C::update( void )
{
  if( strategyPtr )
  {
    strategyPtr->update();
  }
}

//-------------------------------------------------------------------
bool SensorI2C::configMode( BYTE mode, WORD optionIn )
{
  switch( mode )
  {
    case 0:  strategyPtr = &NXTultraschall;   break;
    default: strategyPtr = NULL;              break;
  }

  if( strategyPtr )
  {
    strategyPtr->start( optionIn );
  }
  return true;
}

//EOF
