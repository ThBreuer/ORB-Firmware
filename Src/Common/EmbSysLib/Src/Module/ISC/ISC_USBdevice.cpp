//*******************************************************************
/*!
\file   Module/ISC_USBdevice.cpp
\author Thomas Breuer
\date   11.12.2014, 17.03.2016
*/

//*******************************************************************
#include "lib.h"
#include "Module/ISC.h"

//*******************************************************************
//
// cISC_USBdevice
//
//*******************************************************************
//-------------------------------------------------------------------
cISC_USBdevice::cISC_USBdevice( USBdevice    &usbIn,
                                BYTE          interfId,
                                Crc::MODE     crcMode )

: cISC( crcMode ),
  USBdeviceInterface( usbIn, 1, interfId ),
  usb(usbIn),
  fifo(5)

{
}

//-------------------------------------------------------------------
void cISC_USBdevice::update( void )
{
}

//-------------------------------------------------------------------
void cISC_USBdevice::writeStream( BYTE  id,
                                  BYTE *data,
                                  BYTE  size,
                                  WORD  crc )
{
  cISC_USBdevice_DATA tmp;

  if( size > tmp.maxLength )
  {
    return;
  }
  memcpy( tmp.data, data, size );
  tmp.reserved = 0;
  tmp.id       = id;
  tmp.crcValue = crc;
  fifo << tmp;
  //startTransmission( 0x81 );// todo /****** HACK! *****/ );
}

//-------------------------------------------------------------------
bool cISC_USBdevice::onTransmit( BYTE epId, DataPointer &data ) //cISC_USBdevice_DATA &data )
{
/*  if( fifo >> data )
  {
  }
  else
  {
    memset( data.data, 0, data.maxLength );
    data.id       = 0xFF;
    data.reserved = 0;
    data.crcValue = 0;
  }
  return( true );
  */
      if( !fifo.isEmpty() )
      {
        fifo >> inDataBuffer;
        data = inDataBuffer;
        return( true );
      }
      data = DataPointer(0,0);
      //data = inDataBuffer;

      //isReady=false;// todo /****** HACK! *****/ );

      return( true );

}

//-------------------------------------------------------------------
bool cISC_USBdevice::onReceive( BYTE epId, WORD cnt, DataPointer &data ) //cISC_USBdevice_DATA &data)
{

  DataInterface *ptr = (DataInterface*)list.getFirst();

  //cISC_USBdevice_DATA *dp = (cISC_USBdevice_DATA*)(data.getPtr());

  while( ptr && ptr->id != outDataBuffer.id)
  {
    ptr = (DataInterface*)ptr->getNext();
  }

  if( ptr )
  {
    crc.reset();
    crc((BYTE*)&(outDataBuffer.id), ptr->dataLength+2);
    if( outDataBuffer.crcValue == crc.get() )
    {
      memcpy( ptr->dataRef, outDataBuffer.data, ptr->dataLength );
      ptr->update();
    }
  }
  data = outDataBuffer;

  return( true );

///*  if( /*sizeof(TOUT) == cnt &&*/ !outFifo.isFull() )
//      {
//        outFifo << outDataBuffer;
//      }
//      data = outDataB
//      */
}

//EOF
