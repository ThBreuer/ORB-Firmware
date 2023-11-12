//*******************************************************************
/*!
\file   SensorI2C_TCS3472.cpp
\author Thomas Breuer (Bonn-Rhein-Sieg University of Applied Sciences)
\date   03.02.2021
*/

//*******************************************************************
#include "lib.h"
#include "Module/Rtos/Rtos.h"

//*******************************************************************
#include "SensorI2C_TCS3472.h"
#include "SensorI2C.h"

//*******************************************************************
//
// SensorI2C_TCS3472
//
//*******************************************************************
//-------------------------------------------------------------------
SensorI2C_TCS3472::SensorI2C_TCS3472( SensorI2C &sensor )

: SensorI2C_Strategy( sensor ),
  us( sensor.i2c, 0x29<<1 )
{
}

//-------------------------------------------------------------------
void SensorI2C_TCS3472::start( BYTE option )
{
  BYTE data[] = {0x80 | 0,//reg_enable
                 (1 << 1) // REG_ENABLE_RGBC
                |(1 << 0) //REG_ENABLE_POWER
                };
  us.write( data,2);

  data[0] = 0x80 | 1; //REG_ATIME
  data[1]= 255; // 511,2ms/2,4ms
  us.write(data,2);

  data[0] = 0x80 | 0xf; //REG_AGAIN
  data[1]= 2; // x 16
  us.write(data,2);

  sensor.report.reset( cConfigToORB::Data::SensorConfig::I2C );
}

//-------------------------------------------------------------------
void SensorI2C_TCS3472::stop( void )
{
}

//-------------------------------------------------------------------
void SensorI2C_TCS3472::update( void )
{
  WORD r,g,b;

  //  us.read((BYTE)(0x80 | 0x20 | 0x14),(BYTE*)&c,2);
  us.read( (BYTE)(0x80 | 0x20 | 0x16), &r );
  us.read( (BYTE)(0x80 | 0x20 | 0x18), &g );
  us.read( (BYTE)(0x80 | 0x20 | 0x1A), &b );

  // rrrr rrrr rrgg gggg gggg ggbb bbbb bbbb   red:10bit/green:12bit/blue:10bit
  //            |              |
  //            |              +-- Bit 10
  //            +----------------- Bit 22
  sensor.report.rep.value[0] =   ((r&0x3ff)<<22)
                           | ((g&0x3ff)<<12)
                           | ((b&0x3ff)    );

  sensor.report.setValid();
}

//EOF
