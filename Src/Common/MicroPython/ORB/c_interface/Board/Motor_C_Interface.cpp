#include "stdint.h"
#include "AppTask.h"
#include "lib.h"
#include "Motor_C_Interface.h"

extern "C" {

    void motorSettings(uint8_t port, uint16_t ticsPerRotation,uint8_t acc,uint8_t kp,uint8_t ki ){
        AppTask::configMotor(nullptr ,port,  ticsPerRotation, acc, kp, ki);
        AppTask::wait(nullptr,0); // yield, just wait for next MotorTask running to actualize config
    }


    void setMotor( uint8_t  port, uint8_t  mode, int16_t speed, int pos ){
        AppTask::setMotor(nullptr, port , mode , speed, pos);
    }

    //static motor_return_values values = {.pwr=0,.speed=0,.pos=0};

    void getMotor(uint8_t port, motor_return_values* values)
    {
        ORB::Motor m =  AppTask::getMotor(nullptr, port);

        values->pwr =  m.pwr;
        values->speed = m.speed;
        values->pos = m.pos;

    }

}
