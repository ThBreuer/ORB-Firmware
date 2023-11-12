//*******************************************************************
/*!
\file   SensorI2C_VL53L0X.cpp
\author Thomas Breuer (Bonn-Rhein-Sieg University of Applied Sciences)
\date   03.02.2021
*/

//*******************************************************************
#include "lib.h"
#include "Module/Rtos/Rtos.h"

//*******************************************************************
#include "SensorI2C_VL53L0X.h"
#include "SensorI2C.h"

//*******************************************************************
//
// SensorI2C_VL53L0X
//
//*******************************************************************
//-------------------------------------------------------------------
SensorI2C_VL53L0X::SensorI2C_VL53L0X( SensorI2C &sensor )

: SensorI2C_Strategy( sensor ),
  i2c2( sensor.context.digitalD,
        sensor.context.digitalC,
        400  ),

  s0( sensor.i2c, /*t ,*/ 0 ), // default addr
  s1( i2c2,       /*t2,*/ 0 )  // default addr + 1
{
  isDoubleCh = false;
}

//-------------------------------------------------------------------
void SensorI2C_VL53L0X::start( BYTE option  )
{
  sensor.report.reset( cConfigToORB::Data::SensorConfig::I2C );

  isDoubleCh = (option & 0x01)!=0;

//      cHwI2Cmaster::Device i2cdev(i2c,0x29<<1);
//
//sensor.context.digitalD.setMode( cHwPort::OutOD );
//  sensor.context.digitalC.setMode( cHwPort::OutOD );

//  if(isDoubleCh)
//  {
//      i2c.write(0x8A,0x30); //I2C_SLAVE_DEVICE_ADDRESS, ADDRESS_DEFAULT+addrOffset
//
//
//      sensor.context.digitalH.set(1);
//      sensor.context.digitalD.setMode( cHwPort::OutOD );
//  sensor.context.digitalC.setMode( cHwPort::OutOD );
////
////  sensor.context.digitalD.set( );
////  sensor.context.digitalC.set( );
//  }

  // At power up, both sensors use a default addr.
  // If we want use both sensors, we have to set a second addr:
  // - Reset one sensor
  // - Set a new addr to the sensor, which is not reset
  // - Release the other sensor
//  if( isDoubleCh )
//  {
//    sensor.context.digitalC.setMode( cHwPort::OutOD );
//    sensor.context.digitalC.clr();
//    s0.setAddress(1); // rename, add 1 to default addr
//    sensor.context.digitalC.set();
//
//    // TODO: reset Pin 2 / digitalC back to analog input
//    sensor.context.digitalC.setMode( cHwPort::In );
//  }
/*
  // special feature to re-address a sensor:
  if( option & 0x02 )
  {
    s1.setAddress(0); // rename 0x30 to 0x29
    s0.setAddress(1); // rename 0x29 to 0x30
  }
*/

  sensor.report.rep.value[0]   = 0;
  sensor.report.clrValid();

  s0.init();
  s0.startContinuous();
  s0.setMeasurementTimingBudget(80000);

  if( isDoubleCh )
  {
     sensor.context.digitalD.setMode( Port::OutOD );
     sensor.context.digitalC.setMode( Port::OutOD );

    sensor.context.digitalD.set( );
    sensor.context.digitalC.set( );

    s1.init();
    s1.startContinuous();
    s1.setMeasurementTimingBudget(20000);
  }
}

//-------------------------------------------------------------------
void SensorI2C_VL53L0X::stop( void )
{
}

//-------------------------------------------------------------------
void SensorI2C_VL53L0X::update( void )
{
  sensor.report.rep.value[0] = s0.readRangeSingleMillimeters() & 0xFFFF;

  if( isDoubleCh )
  {
    sensor.report.rep.value[0] |= s1.readRangeSingleMillimeters()<<16;
  }


  if( s0.timeoutOccurred() || (isDoubleCh && s1.timeoutOccurred()))
    sensor.report.clrValid();
  else
    sensor.report.setValid();
}


//EOF
