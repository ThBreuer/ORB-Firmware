//*******************************************************************
/*!
\file   Module/ISC_UART.h
\author Thomas Breuer
\date   11.12.2014, 17.03.2016
*/

//*******************************************************************
#ifndef _ISC_UART_H
#define _ISC_UART_H

//*******************************************************************
#include "Module/ISC.h"

//*******************************************************************
/*!
\class cISC_UART

\brief ISC transport class with UART hardware

\remark The length of the payload is limited to 64 bytes

\example cISC.cpp
*/
class cISC_UART : public cISC
{
  private:
    //---------------------------------------------------------------
    #pragma pack(1)
    class DATA
    {
      public:
        static const WORD maxLength = 60;

        WORD crcValue;
        BYTE id;
        BYTE reserved;
        BYTE data[ maxLength ];

    };
    #pragma pack()

  public:
    //---------------------------------------------------------------
    /*! Instantiate an ISC transport object with UART hardware

        \param uart Reference to UART hardware
        \param crcMode Select CRC calculation mode (FAST or SMALL)
    */
    cISC_UART( Uart    &uart,
               cCRC::MODE  crcMode = cCRC::SMALL );

    //---------------------------------------------------------------
    /*! Update the ISC transport object

        Checks, if new data are arrived. In that case ISC copies the
        data to identified data object, sets the new data flag and
        calls the related \b update() method.
    */
    virtual void update( void );

  private:
    //---------------------------------------------------------------
    void concatByte( BYTE *buf, WORD &pos, BYTE data )
    {
      switch( data )
      {
        case  0xA0: buf[pos++] = 0xA0;
                    buf[pos++] = 0x00;
                    break;
        case  0xA1: buf[pos++] = 0xA0;
                    buf[pos++] = 0x01;
                    break;
        case  0xA2: buf[pos++] = 0xA0;
                    buf[pos++] = 0x02;
                    break;
        default:    buf[pos++] = data;
                    break;
      }
    }

    //---------------------------------------------------------------
    virtual void writeStream( BYTE  id,
                              BYTE *data,
                              BYTE  size,
                              WORD  crc );

  private:
    //---------------------------------------------------------------
    Uart &uart;

      WORD crcValue;
      BYTE id;
      BYTE reserved;

      DATA rec;

    bool     error;
    WORD     errorCnt;
    BYTE     idx;
    BYTE     ready;
    BYTE     length;
    BYTE     state;

    BYTE     prev;

    bool flag;

}; //cISC_UART

#endif
