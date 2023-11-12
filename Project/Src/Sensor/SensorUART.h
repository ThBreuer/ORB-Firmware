//*******************************************************************
/*!
\file   SensorUART.h
\author Thomas Breuer (Bonn-Rhein-Sieg University of Applied Sciences)
\date   03.02.2021
*/

//*******************************************************************
#ifndef _SENSOR_UART_H
#define _SENSOR_UART_H

//*******************************************************************
#include "UART_Ext.h"
#include "Sensor.h"

//*******************************************************************
/*!
\class
\brief
*/
//*******************************************************************
class SensorUART : public Sensor
{
  private:
    //*******************************************************************
    /*!
    \class SensorUART::Properties
    \brief
    */
    class Properties
    {
      public:
        //-----------------------------------------------------------
        Properties()
        {
          type = 0;
          numOfModes = 0;
          modesInView = 0;
          speed = 2400;
        }

      public:
        //-----------------------------------------------------------
        BYTE  type;
        BYTE  numOfModes;
        BYTE  modesInView;
        DWORD speed;
    };

  private:
    //---------------------------------------------------------------
    cHwUART_Ext &uart;
    BYTE         buf[32];
    Properties   p;
    int          currentMode;
    int          currentCmd;
    BYTE         option;
    BYTE         state;
    BYTE         sensorType;
    BYTE         skip_IR_Error;
    unsigned     errCnt;

  public:
    //---------------------------------------------------------------
    SensorUART( Sensor::Context &context,
                cHwUART_Ext     &sIn     );

  private:
    //---------------------------------------------------------------
    virtual void start();

    //---------------------------------------------------------------
    virtual void stop( void );

    //---------------------------------------------------------------
    virtual void update( void );

  private:
    //---------------------------------------------------------------
    BYTE getLength( BYTE c )
    {
        return( 1<<((c>>3) & 0x07) );
    }

    //---------------------------------------------------------------
    BYTE getMode( BYTE c )
    {
        return( c & 0x07 );
    }

    //---------------------------------------------------------------
    bool sendMode( BYTE mode );

    //---------------------------------------------------------------
    virtual bool configMode( BYTE mode, WORD option );

    //---------------------------------------------------------------
    BYTE nextSample();

    //---------------------------------------------------------------
    bool read(BYTE check, BYTE len);

    //---------------------------------------------------------------
    void sendByte(BYTE msg);

    //---------------------------------------------------------------
    void setBaudrate(float rate);

    //---------------------------------------------------------------
    virtual void reset();

};

#endif
