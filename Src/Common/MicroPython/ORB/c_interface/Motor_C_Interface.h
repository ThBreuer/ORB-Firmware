//*******************************************************************
/*!
\author Nils Hoffmann
\date   12.10.2024
*/

#ifndef MOTOR_MOCKUP_H
#define MOTOR_MOCKUP_H
#include "stdint.h"
#include "stddef.h"

#ifdef __cplusplus
extern "C" {
#endif


enum
{
  M1  = 0x00,
  M2,
  M3,
  M4
};

enum
{
  POWER_MODE  = 0,
  BRAKE_MODE  = 1,
  SPEED_MODE  = 2,
  MOVETO_MODE = 3,
};

void motorSettings(uint8_t port, uint16_t ticsPerRotation,uint8_t acc,uint8_t kp,uint8_t ki );

void setMotor( uint8_t  port, uint8_t  mode, int16_t speed, int pos );

typedef struct {
	int16_t pwr;
	int16_t speed;
	int pos;
}motor_return_values;

void getMotor(uint8_t port, motor_return_values* values);



#ifdef __cplusplus
}
#endif


#endif // MOTOR_H
