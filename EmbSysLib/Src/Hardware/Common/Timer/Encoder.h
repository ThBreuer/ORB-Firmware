//*******************************************************************
/*!
\file   Encoder.h
\author Thomas Breuer (Bonn-Rhein-Sieg University of Applied Sciences)
\date   23.03.2016

This file is released under the MIT License.
*/

//*******************************************************************
#ifndef _HW_ENCODER_H
#define _HW_ENCODER_H

//*******************************************************************

#include "Hardware/Common/Port/Port.h"
#include "Hardware/Common/Timer/Timer.h"


using namespace EmbSysLib::Hw;

//*******************************************************************
/*!
\class cHwEncoder

\brief Abstract class supporting a quadratur encoder

\example cHwEncoder.cpp
*/
class cHwEncoder
{
  public:
    //---------------------------------------------------------------
    /*! \enum Mode
        \brief Define encoder operating modes
    */
    typedef enum
    {
      NORMAL  = 0x00, //!< Normal count direction
      REVERSE = 0x01  //!< Reverse count direction
    } Mode;

  protected:
    //---------------------------------------------------------------
    // Standard constructor
    //
    cHwEncoder( Mode modeIn )
    {
      mode = modeIn;
    }

  public:
    //---------------------------------------------------------------
    /*! Get and reset counter
        \return Steps since last call of this function
    */
    virtual int get( void ) = 0;


  protected:
    //---------------------------------------------------------------
    Mode mode;

}; //cHwEncoder

//*******************************************************************
/*!
\class cHwEncoder_Emul

\todo Add documentation
*/
class cHwEncoder_Emul : public cHwEncoder, Timer::Task
{
  public:
    //---------------------------------------------------------------
    cHwEncoder_Emul( Port::Pin &pinAIn,
                     Port::Pin &pinBIn,
                     Timer     &timer,
                     Mode          modeIn )
    : cHwEncoder( modeIn ),
      pinA( pinAIn ),
      pinB( pinBIn )
      {
          pinA.setMode( Port::In );
          pinB.setMode( Port::In );
          timer.add( this );
          A_last = 0;
          B_last = 0;
          cnt    = 0;
      }

    //---------------------------------------------------------------
    virtual void update( void )
    {
      BYTE A_new = pinA.get();
      BYTE B_new = pinB.get();

     System::disableInterrupt();

      if( A_new != A_last )
      {
          if( A_new == B_new )
          {
            cnt++;
          }
          else
          {
            cnt--;
          }
      }
      else if( B_new != B_last )
      {
          if( B_new != A_new )
          {
            cnt++;
          }
          else
          {
            cnt--;
          }
      }
      System::enableInterrupt();

      A_last = A_new;
      B_last = B_new;
    }

    //---------------------------------------------------------------
    virtual int get( void )
    {
        System::disableInterrupt();
        int ret = cnt;
        cnt = 0;
        System::enableInterrupt();
        return( (mode&REVERSE)?ret:-ret );
    }

  private:
    //---------------------------------------------------------------
    Port::Pin &pinA;
    Port::Pin &pinB;
    BYTE A_last;
    BYTE B_last;

    int cnt;
};

#endif
