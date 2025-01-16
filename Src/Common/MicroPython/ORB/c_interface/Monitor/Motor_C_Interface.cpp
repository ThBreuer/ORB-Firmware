//*******************************************************************
/*!
\author Thomas Breuer
\date   12.10.2024
*/

#include "Motor_C_Interface.h"
#include <stdio.h>
#include <stdint.h>

#include "Daten.h"

#ifdef __cplusplus
extern "C" {
#endif

extern Daten            daten;

void motorSettings(uint8_t port, uint16_t ticsPerRotation,uint8_t acc,uint8_t kp,uint8_t ki )
{
    //printf("motor settings\nport(%u) ticks(%u) acc(%u) kp(%u) ki(%u)\n",port,  ticsPerRotation, acc, kp, ki);

    if( port < 4)
    {
      Daten::ConfigToORB::Data conf = daten.config.d.data;
      conf.motor[port].ticsPerRotation = ticsPerRotation;
      conf.motor[port].acceleration = acc;
      conf.motor[port].Regler_Kp = kp;
      conf.motor[port].Regler_Ki = ki;
      daten.config << conf;
    }
}

void setMotor( uint8_t  port, uint8_t  mode, int16_t speed, int pos )
{
    //printf("set motor port(%d) mode(%d) speed(%d) pos(%d)\n", port , mode , speed, pos);

    if( port < 4)
    {
      Daten::PropToORB::Data prop = daten.control.d.data;
      prop.motor[port].mmode = mode;
      prop.motor[port].speed = speed;
      prop.motor[port].pos   = pos;
      daten.control << prop;
    }
}

//static motor_return_values values = {.pwr=0,.speed=0,.pos=0};

void getMotor(uint8_t port, motor_return_values *values)
{
  if( port < 4 )
  {
    Daten::PropFromORB::Data::Motor &m = daten.mess.d.data.motor[port];
    values->pwr   = m.pwr;
    values->speed = m.speed;
    values->pos   = m.pos;
  }
    //return &values;
}


#ifdef __cplusplus
}
#endif

