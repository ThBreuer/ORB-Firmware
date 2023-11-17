//*******************************************************************
/*!
\file   SensorTouch.cpp
\author Thomas Breuer (Bonn-Rhein-Sieg University of Applied Sciences)
\date   03.02.2021
*/

//*******************************************************************
#include "lib.h"

//*******************************************************************
#include "SensorTouch.h"

//*******************************************************************
//
// SensorTouch
//
//*******************************************************************
/*
  NXT-Touch: Pin1: R2.2k+Taster->Gnd
             Pin2: Gnd
             Pin3: Gnd
             Pin4: nc
             Pin5: nc
             Pin6: nc

  EV2-Touch: Pin1: R910->Gnd
             Pin2: nc
             Pin3: Gnd
             Pin4: R2.2k+Taster->Signal
             Pin5: Gnd
             Pin6: Signal

  Messwerte:
                          NXT            EV3
                          offen  geschl  offen  geschl
    Pin1(C) analog(3)     high   low(1)  low(2) low(2)
    Pin2(D) analog        0      0       nc     nc
    Pin5(A) digital,PU    1      1       0      0
    Pin6(B) digital,PD    0      0       0      1

    (1) 2.2/(2.2+6.8)*3.3V = 0,8V = 993 / 15887
    (2) 0,91/(0,91+6.8)*3.3V = 0,39V = 483 / 7745
    (3) Hardware-Pull-Up (6,8k)
*/
//-------------------------------------------------------------------
SensorTouch::SensorTouch( Sensor::Context &context )

: Sensor( context )

{
}

//-------------------------------------------------------------------
void SensorTouch::start( void )
{
  report.reset( cConfigToORB::Data::SensorConfig::TOUCH );
  report.setValid();

  context.adc1.enable();
  context.digitalA.setMode( Port::InPU );
  context.digitalB.setMode( Port::InPD );
}

//-------------------------------------------------------------------
void SensorTouch::stop( void )
{
  context.digitalA.setMode( Port::InPU );
  context.digitalA.set();
  context.digitalB.setMode( Port::InPU );
  context.digitalB.set();
}

//-------------------------------------------------------------------
void SensorTouch::update( void )
{
  if( context.digitalA.get() )
  {// NXT
    if( context.adc1.getRaw() < 0x8000 ) // < 1,65V
      report.rep.value[0] = 1;
    else
      report.rep.value[0] = 0;
  }
  else
  {// EV3
    report.rep.value[0] = context.digitalB.get();
  }
}

//-------------------------------------------------------------------
bool SensorTouch::configMode( BYTE mode, WORD option )
{
  return true;
}

//EOF
