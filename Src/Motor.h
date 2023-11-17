//*******************************************************************
//*******************************************************************
/*!
\file   Motor.h
\author Thomas Breuer (Bonn-Rhein-Sieg University of Applied Sciences)
\date   03.02.2021
*/

//*******************************************************************
#ifndef _MOTOR_H
#define _MOTOR_H

//*******************************************************************
#include "lib.h"
#include "MovingAverage.h"
#include "ORB.h"

//*******************************************************************
/*!
\class Motor
\brief
*/
class Motor
{
  public:
    //-------------------------------------------------------
    typedef enum
    {
      FREE     = 0,
      BRAKE    = 1,
      SPEED    = 2,
      POSITION = 3
    } ControlMode;

    //---------------------------------------------------------------
    class Setting
    {
      public:
        ControlMode mode;
        float       speed;
        int         pos;
    };

    //---------------------------------------------------------------
    class Config
    {
      public:
        float ticsToRot; // Umrechnungsfaktor Tics to 1/1000 Umdrehung
        float acc;
        float Regler_Kp; //------------------------------------------
        float Regler_Ki;
    };

  public:
    //---------------------------------------------------------------
    Motor( cDevMotor  &motor,
           cHwEncoder &encIn );

    //---------------------------------------------------------------
    virtual void update( void );

  private:
    //---------------------------------------------------------------
    void speedControl( float speed );

    //---------------------------------------------------------------
    void positionControl( float speedLimit, int pos );

  public:
    //---------------------------------------------------------------
    cSharedMem<ORB::Motor >  reportBuffer;
    cSharedMem<Setting    >  settingBuffer;
    cSharedMem<Config     >  configBuffer;

  private:
    //---------------------------------------------------------------
    cDevMotor   &motor;
    cHwEncoder  &enc;

    ORB::Motor  report;
    Setting     setting;
    Config      config;

    float measuredSpeed;
    int   measuredPos;

    float power;
    float deltaLast;
    float posSpeed;
    bool  isPosCtrlRunning;

    MovingAverage<20> movingAverage;

};

#endif
