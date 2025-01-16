//*******************************************************************
/*!
\file   ISC_USBhost.cpp
\author Thomas Breuer
\date   11.12.2014
*/

//*******************************************************************
#include "lib.h"
#include "ISC_USBhost.h"


//*******************************************************************
//
// cISC_USBhost
//
//*******************************************************************
//-------------------------------------------------------------------
cISC_USBhost::cISC_USBhost( USBhost &usbIn, BYTE interfId, Crc::MODE crcMode )

: cISC( crcMode ),
  usb(usbIn)

{

}

//-------------------------------------------------------------------
void cISC_USBhost::update( void )
{
  DATA rec;

  // \todo check this
  if( !usb.readInterrupt( rec ) )
  {
  //  flag |= true;
  return;
  }

 DataInterface *ptr = (DataInterface*)list.getFirst();

  while( ptr && ptr->id != rec.id)
  {
    ptr = (DataInterface*)ptr->getNext();
  }

  if( ptr )
  {
    crc.reset();
    crc((BYTE*)&rec.id, ptr->dataLength+2);

    if( rec.crcValue == crc.get() )
    {
      for(BYTE i = 0; i < ptr->dataLength; i++ )
      {
        ptr->dataRef[i] = rec.data[i];
      }
      ptr->update();
    }
  }
  return; //( true );
}

//-------------------------------------------------------------------
void cISC_USBhost::writeStream( BYTE id, BYTE *data, BYTE size, WORD crc )
{
  DATA tmp;

  if( size > tmp.maxLength )
  {
    return;
  }

  memcpy( tmp.data, data, size );
  tmp.reserved = 0;
  tmp.id       = id;
  tmp.crcValue = crc;

  usb.writeInterrupt( (BYTE*)&tmp, size+4 ); //sizeof(cISC_DATA) );
}


//EOF
