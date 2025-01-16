//*******************************************************************
/*!
\file   devMotorBipolar.h
\author Thomas Breuer
\date   22.02.2019
*/

//*******************************************************************
#ifndef _DEV_MOTOR_BIPOLAR_H
#define _DEV_MOTOR_BIPOLAR_H

//*******************************************************************
using namespace EmbSysLib::Dev;

//*******************************************************************
/*!
\class   cDevMotorBipolar


\example
*/
class cDevMotorBipolar : public cDevMotor
{
  private:
    //---------------------------------------------------------------
    AnalogOut  &plus;
    AnalogOut  &minus;

  public:
    //---------------------------------------------------------------
    // Konstruktor
    //
    cDevMotorBipolar( AnalogOut &plus,
                      AnalogOut &minus );

  public:
    //---------------------------------------------------------------
    /*!
    */
    virtual void run( float power );

    //---------------------------------------------------------------
    /*!
    */
 	  virtual void brake( void );

};

#endif
