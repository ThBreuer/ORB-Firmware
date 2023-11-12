//*******************************************************************
/*!
\file   SensorAnalog.cpp
\author Thomas Breuer (Bonn-Rhein-Sieg University of Applied Sciences)
\date   03.02.2021
*/

//*******************************************************************
#include "lib.h"

//*******************************************************************
#include "SensorAnalog.h"

//*******************************************************************
//
// SensorAnalog
//
//*******************************************************************
//-------------------------------------------------------------------
SensorAnalog::SensorAnalog( Sensor::Context &context )

  : Sensor( context )
{
}

//-------------------------------------------------------------------
void SensorAnalog::start( void )
{

  report.reset( cConfigToORB::Data::SensorConfig::ANALOG );


  context.digitalA.set();
  context.digitalB.set();

/// TODO: Pin-Config aus option uebernehmen
  context.digitalA.setMode( Port::InPU  );

  // vorläufig:
////////  context.digitalA.setMode( Port::OutPP );

  context.digitalB.setMode( Port::InPU  );

  context.adc1.enable();
  context.adc2.enable();

}

//-------------------------------------------------------------------
void SensorAnalog::stop( void )
{
  context.digitalA.setMode( Port::InPU );
  context.digitalA.set();
}

//-------------------------------------------------------------------
void SensorAnalog::update( void )
{
  WORD analog1 = context.adc1.getRaw()>>4;
  WORD analog2 = context.adc2.getRaw()>>4;
  WORD pin5    = context.digitalA.get();
  WORD pin6    = context.digitalB.get();

  report.rep.value[0] =   ((DWORD)(analog1 & 0x0FFF)     )
                        | ((DWORD)(analog2 & 0x0FFF) <<12)
                        | ((DWORD)(pin6    & 0x0001) <<24)
                        | ((DWORD)(pin5    & 0x0001) <<25);
  report.setValid();

}

//-------------------------------------------------------------------
bool SensorAnalog::configMode( BYTE mode, WORD option )
{

  setPinMode( context.digitalC, option>> 0 );  //pin 1
  setPinMode( context.digitalD, option>> 4 );  //pin 2
  setPinMode( context.digitalA, option>> 8 );  //pin 5
  setPinMode( context.digitalB, option>>12 );  //pin 6

  return true;
}

//-------------------------------------------------------------------
 void SensorAnalog::setPinMode( Port::Pin &pin, BYTE mode )
{
  switch( mode & 0x07 )
  {
    case 0:  /* ? */                    break;
    case 1:  /*analog ? */              break;
    case 2:  pin.setMode( Port::In   ); break;
    case 3:  pin.setMode( Port::InPU ); break;
    case 4:  pin.setMode( Port::InPD ); break;
    case 5:  pin.setMode( Port::OutOD); break;
    case 6:  pin.setMode( Port::OutPU); break;
    case 7:  pin.setMode( Port::OutPP); break;
    default:                            break;
  }

  if( (mode & 0x07) >= 2 )
      pin.set( mode&0x08 );
}


//EOF
