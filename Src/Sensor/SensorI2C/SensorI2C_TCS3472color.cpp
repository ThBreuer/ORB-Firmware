//*******************************************************************
/*
\file   SensorI2C_TCS3472color.cpp
\author Thomas Breuer (Bonn-Rhein-Sieg University of Applied Sciences)
\date   23.05.2025
*/

//*******************************************************************
#include "lib.h"
#include "Module/Rtos/Rtos.h"

//*******************************************************************
#include "SensorI2C_TCS3472color.h"
#include "SensorI2C.h"

//*******************************************************************
//
// SensorI2C_TCS3472color
//
// todo Varianten TCS3472:  addr 0x29   data reg at 0xB6 (0x80|0x20|0x19)
//                TCS34007: addr 0x29   data reg at 0x96
//                TCS34001: addr 0x39   data reg at 0x96
//
//*******************************************************************
//-------------------------------------------------------------------
SensorI2C_TCS3472color::SensorI2C_TCS3472color( SensorI2C &sensorIn )
    : SensorI2C_Strategy( sensorIn ),
      us(sensorIn.i2c, 0x39<<1) // todo the popular alternative tcs3472 has addr 0x29, use option???
{
}

//-------------------------------------------------------------------
void SensorI2C_TCS3472color::start( BYTE option )
{
  BYTE id=0;
  us.setHwAddr( 0x39<<1 );
  us.read((BYTE)(0x80|0x12),(BYTE*)&id);
  if( us.isError() )
  {
    us.setHwAddr( 0x29<<1 );
  }
  
  // todo reread ID, handle error, if device not available

  us.write( (BYTE)(0x80|0x00), //reg_enable
            (BYTE)((1<<0) ));   //REG_ENABLE_POWER

  System::delayMilliSec(3);

  us.write( (BYTE)(0x80|0x00), //reg_enable
            (BYTE)((1<<1)|(1 << 0)) );   //// REG_ENABLE_RGBC  REG_ENABLE_POWER

  us.write( (BYTE)(0x80|0x01), //REG_ATIME
            (BYTE)(255 ) );   // 511,2ms/2,4ms

  us.write( (BYTE)(0x80|0x0f), //
            (BYTE)(2) );   // x 16  // todo: gain from option?

  sensor.report.reset( cConfigToORB::Data::SensorConfig::I2C );
}

//-------------------------------------------------------------------
void SensorI2C_TCS3472color::stop( void )
{
}

//-------------------------------------------------------------------
void SensorI2C_TCS3472color::update( void )
{
  BYTE commandState;
  BYTE value = 0;

  Data data;

  us.read((BYTE)(0x80 /*| 0x20 tcs3472*/ | 0x16), &data);
  if( !us.isError() )
  {

    //  r=MIN(255.0,100.0*(float)r/(float)(c+1));
    //  g=MIN(255.0,100.0*(float)g/(float)(c+1));
    //  b=MIN(255.0,100.0*(float)b/(float)(c+1));
    //  c = MIN((WORD)0x3FF,c)>>2;
    //    sensor.report.value   = ((DWORD)c<<24)|((DWORD)r<<16)|((DWORD)g<<8)|(DWORD)b;  // ???
    //    sensor.report.isValid = true;


    // rrrr rrrr rrgg gggg gggg ggbb bbbb bbbb   red:10bit/green:12bit/blue:10bit
    //            |              |
    //            |              +-- Bit 10
    //            +----------------- Bit 22
    sensor.report.rep.value[0]   =  ((DWORD)(MIN(data.r,(WORD)1023)&0x3ff)<<22)
                                   |((DWORD)(MIN(data.g,(WORD)1023)&0x3ff)<<12)
                                   |((DWORD)(MIN(data.b,(WORD)1023)&0x3ff)    );
    sensor.report.setValid();
  }
  else
  {
    sensor.report.clrValid();
  }
}


//EOF
