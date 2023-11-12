//*******************************************************************
/*!
\file   Module/ISC_UART.cpp
\author Thomas Breuer
\date   11.12.2014, 17.03.2016
*/

//*******************************************************************
#include "lib.h"
#include "Module/ISC.h"

//*******************************************************************
//
// cISC_UART
//
//*******************************************************************
/*
  In order to achieve a fast synchronisation of the data stream
  without using a timeout, each byte of the payload is devided in
  two parts. The payload is bit-or operated with an
  identifier befor sending. To synchronize the data stream, just wait
  until 0001 xxxx is received.

  Byte | 7654 3210
  ---- | ---- ----
  0    | 0001 high part of low byte crc
  1    | 0010 low  part of low byte crc
  2    | 0011 high part of high byte crc
  3    | 0100 low  part of high byte crc
  4    | 0101 high part of identifier
  5    | 0110 low  part of identifier
  6    | 0111 high part of reserved
  7    | 1000 low  part of reserved
  ...
  2i+8 | 1001 high part of data byte i
  2i+9 | 1010 low  part of data byte i
  ...
  2N+6 | 1011 high part of data byte N-1
  2N+7 | 1100 low  part of data byte N-1
*/
//-------------------------------------------------------------------
cISC_UART::cISC_UART( Uart &uartIn, cCRC::MODE crcMode )
: cISC( crcMode ),
  uart(uartIn)
{
  idx = 0;
  state = 0x90;
  error = false;
  ready = false;

  prev = 0;
}


//-------------------------------------------------------------------
void cISC_UART::writeStream( BYTE  id,
                             BYTE *data,
                             BYTE  size,
                             WORD  crc )
{
  BYTE  buf[ 2*DATA::maxLength + 10 ];
  WORD pos = 0;

  if( size < 2 || DATA::maxLength < size )
  {
    return;
  }

  buf[pos++] = 0xA1; // start

  concatByte( buf, pos, (crc   )&0xFF ); // crc, low byte
  concatByte( buf, pos, (crc>>8)&0xFF ); // crc, high byte
  concatByte( buf, pos,            id ); // id
  concatByte( buf, pos,          0x00 ); // reserved

  for( BYTE i=0; i<size; i++ )
  {
    concatByte( buf, pos, data[i] ); // data[],
  }

  buf[pos++] = 0xA2; // stop

  uart.set( buf, pos );
}

//-------------------------------------------------------------------
// Parse and synchronize incomming data stream
void cISC_UART::update( void )
{
  BYTE c;


  while( uart.get(c) )
  {
    switch( c )
    {
      case 0xA1: // START
        idx = 0;
        flag = false;
        break;

      case 0xA2: // STOP
        ready = true;
        flag = false;
        break;

     case 0xA0: //
         flag = true;
         break;

     default:
         if( flag )
         {
            c += 0xA0;
         }
         ((BYTE*)(&rec))[idx++] = c;
         flag = false;
         break;
    }

    if( idx > sizeof(DATA) )
    {
      error = true;
      flag = false;
    }

    if( error )
    {
      error = false;
      ready = false;
      idx   = 0;
      errorCnt++;
    }

    if( ready )
    {
      ready = false;
      flag = false;
      // look up correct data object: identifier and length OK?
      DataInterface *ptr = (DataInterface*)list.getFirst();

      while( ptr && ptr->id != rec.id )
      {
        ptr = (DataInterface*)ptr->getNext();
      }

      if(    ptr
          && idx == ptr->dataLength + 4
          && rec.crcValue == crc( (BYTE*)&rec.id, idx-2 ) )
      {
        memcpy( ptr->dataRef, rec.data, ptr->dataLength );
        ptr->update(); // we found a matching data object
      }
      else
      {
          errorCnt++;
      }
      idx   = 0;
    }
  }
}

//EOF
