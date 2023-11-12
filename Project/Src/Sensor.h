//*******************************************************************
/*!
\file   Sensor.h
\author Thomas Breuer (Bonn-Rhein-Sieg University of Applied Sciences)
\date   03.02.2021
*/

//*******************************************************************
#ifndef _SENSOR_H
#define _SENSOR_H

//*******************************************************************
#include "Properties.h"
#include "ORB.h"

//*******************************************************************
/*!
\class Sensor
\brief
*/
class Sensor
{
  public:
    //***************************************************************
    /*!
    \class Sensor::Context
    \brief
    */
    class Context
    {
      public:
        //-----------------------------------------------------------
        Context( cDevAnalogIn &adc1In,
                 cDevAnalogIn &adc2In,
                 Port::Pin &digitalA,
                 Port::Pin &digitalB,
                 Port::Pin &digitalC,
                 Port::Pin &digitalD,
                 Port::Pin &digitalH  );


      public:
        //-----------------------------------------------------------
        cDevAnalogIn  &adc1;
        cDevAnalogIn  &adc2;
        Port::Pin  &digitalA;
        Port::Pin  &digitalB;
        Port::Pin  &digitalC;
        Port::Pin  &digitalD;
        Port::Pin  &digitalH;
    };

  public:
    //***************************************************************
    /*!
    \class Sensor::Report
    \brief
    */
    class Report
    {
      public:
        //-----------------------------------------------------------
        ORB::Sensor rep;

        //-----------------------------------------------------------
        void reset( BYTE _type )
        {
          rep.type     = _type;
          rep.option   = 0;
          rep.lenExp   = 0;
          rep.value[0] = 0;
          rep.value[1] = 0;
        }

        //-----------------------------------------------------------
        void setValid() {rep.type |=  0x80;}
        void clrValid() {rep.type &= ~0x80;}
    };

  public:
    //---------------------------------------------------------------
    Sensor( Sensor::Context &context );

    //---------------------------------------------------------------
    virtual void start( void ) = 0;

    //---------------------------------------------------------------
    virtual void stop( void ) = 0;

    //---------------------------------------------------------------
    virtual void update( void ) = 0;

    //---------------------------------------------------------------
    virtual bool configMode( BYTE mode, WORD optionIn ) = 0;

  public:
    //---------------------------------------------------------------
    Sensor::Report   report;
    Sensor::Context &context;

};

#endif
