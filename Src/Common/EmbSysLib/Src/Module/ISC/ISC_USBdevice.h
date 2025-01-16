//*******************************************************************
/*!
\file   Module/ISC_USBdevice.h
\author Thomas Breuer
\date   11.12.2014, 17.03.2016
*/

//*******************************************************************
#ifndef _ISC_USB_DEVICE_H
#define _ISC_USB_DEVICE_H

//*******************************************************************
#include "Module/ISC.h"
#include "Module/USB/USBdeviceSimpleIO.h"

//*******************************************************************
/*!
\class cISC_USBdevice

\brief ISC transport class with USB hardware

\remark The length of the payload is limited to 60 bytes

\example cISC.cpp
*/
    //---------------------------------------------------------------
    #pragma pack(1)
    class cISC_USBdevice_DATA
    {
      public:
        static const WORD maxLength = 60;

        WORD crcValue;
        BYTE id;
        BYTE reserved;
        BYTE data[ maxLength ];

    };
    #pragma pack()

class cISC_USBdevice : public cISC,
//                       public USBdeviceSimpleIO< cISC_USBdevice_DATA, cISC_USBdevice_DATA >
                       public USBdeviceInterface
{
  public:
    //---------------------------------------------------------------
    /*! Instantiate an ISC transport object with USB interface

        \param uart Reference to USB hardware
        \param interfId USB interface ID
        \param crcMode Select CRC calculation mode (FAST or SMALL)
    */
    cISC_USBdevice( USBdevice    &usb,
                    BYTE       interfId,
                    Crc::MODE  crcMode = Crc::SMALL );

    //---------------------------------------------------------------
    /*! Update the ISC transport object

        NOT required with USB
    */
     virtual void update( void );

   private:
    //---------------------------------------------------------------
    virtual void writeStream( BYTE  id,
                              BYTE *data,
                              BYTE  size,
                              WORD  crc );

   //---------------------------------------------------------------
    virtual void onConfigEndpoint( BYTE epId, DataPointer &data, WORD maxPacketSize )
    {
      if( epId & 0x80 )
      {
        data = inDataBuffer;
      }
      else
      {
        data = outDataBuffer;
      }
    }

    //---------------------------------------------------------------
    virtual bool onTransmit( BYTE epId, DataPointer &epData );

    //---------------------------------------------------------------
    virtual bool onReceive( BYTE epId, WORD cnt, DataPointer &data );

  private:
    //---------------------------------------------------------------
    USBdevice &usb;


    //---------------------------------------------------------------
    cISC_USBdevice_DATA outDataBuffer;
    cISC_USBdevice_DATA  inDataBuffer;

    Fifo<cISC_USBdevice_DATA> fifo;

}; //cISC_USBdevice

#endif
