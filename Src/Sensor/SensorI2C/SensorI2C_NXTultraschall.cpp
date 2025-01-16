//*******************************************************************
/*!
\file   SensorI2C_NXTultraschall.cpp
\author Thomas Breuer (Bonn-Rhein-Sieg University of Applied Sciences)
\date   03.02.2021
*/

//*******************************************************************
#include "lib.h"
#include "Module/Rtos/Rtos.h"

//*******************************************************************
#include "SensorI2C_NXTultraschall.h"
#include "SensorI2C.h"

//*******************************************************************
//
// SensorI2C_NXT_ULTRASCHALL
//
//*******************************************************************
//-------------------------------------------------------------------
SensorI2C_NXTultraschall::SensorI2C_NXTultraschall( SensorI2C &sensor )

: SensorI2C_Strategy( sensor ),
  //i2c( sensor.scl, sensor.sda, 10 ),
  us ( sensor.i2c, 0x02)
{
}

//-------------------------------------------------------------------
void SensorI2C_NXTultraschall::start( BYTE option )
{
//  sensor.scl.setMode( Port::OutPU );
//  sensor.sda.setMode( Port::OutPU );

  sensor.context.digitalD.set( 1 );
  sensor.context.digitalD.setMode( Port::OutPP);

  ///sensor.context.digitalH.clr();

  sensor.report.reset( cConfigToORB::Data::SensorConfig::I2C );
}

//-------------------------------------------------------------------
void SensorI2C_NXTultraschall::stop( void )
{
  sensor.context.digitalD.setMode( Port::In);
  sensor.context.digitalD.set( 0 );


  sensor.context.digitalH.set(1);
}

//-------------------------------------------------------------------
void SensorI2C_NXTultraschall::update( void )
{
  BYTE commandState;
  BYTE value = 0;

  Rtos::Clock timerLoc( 20 );

  us.write( (BYTE)0x41 );
  commandState = us.read();
  timerLoc.start();
  while( !timerLoc.timeout() );

  if( commandState == 0x02 )
  {
    us.write( (BYTE)0x42 );
    value = us.read();
    timerLoc.start();
    while( !timerLoc.timeout() );
  }

  if( !us.isError() && commandState == 0x02 )
  {
    sensor.report.rep.value[0]   = value;
    sensor.report.setValid();
  }
  else
  {
    // Error
    sensor.report.rep.value[0]   = 255;  // ???
    sensor.report.clrValid();
  }
}

//EOF
