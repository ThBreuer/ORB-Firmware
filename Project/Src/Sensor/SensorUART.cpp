//*******************************************************************
/*!
\file   SensorUART.cpp
\author Thomas Breuer (Bonn-Rhein-Sieg University of Applied Sciences)
\date   03.02.2021
*/

//*******************************************************************
#include "lib.h"
#include "Module/Rtos/Rtos.h"
#include "SensorUART.h"

//*******************************************************************
#define SYS_SYNC       0x00
#define SYS_NACK       0x02
#define SYS_ACK        0x04

#define CMD_ACK_REQ    0x04

#define CMD_SELECT     0x43
#define CMD_TYPE       0x40
#define CMD_MODES      0x49
#define CMD_SPEED      0x52
#define CMD_WRITE      0x44

#define INFO_MSG       0x80
#define INFO_MASK      0xC0
#define INFO_LLL       0x38
#define INFO_MMM       0x07
#define INFO_NAME      0x00
#define INFO_RAW       0x01
#define INFO_PCT       0x02
#define INFO_SI        0x03
#define INFO_SYM       0x04
#define INFO_FOR       0x80

#define DATA_MASK      0xC0

//*******************************************************************
//
// SensorUART
//
//*******************************************************************
//-------------------------------------------------------------------
SensorUART::SensorUART( Sensor::Context &context,
                        cHwUART_Ext     &sIn     )

  : Sensor( context ),
    uart(sIn)
{
  currentMode    = 0;
}

//-------------------------------------------------------------------
void SensorUART::start( void )
{
  report.reset( cConfigToORB::Data::SensorConfig::UART );

  context.digitalA.setMode( Port::InPU  );
  context.digitalB.setMode( Port::InPU  );

  uart.connectToPort();

  state         = 0;
  skip_IR_Error = 0;

  setBaudrate( 2400 );

  reset();
}

//-------------------------------------------------------------------
void SensorUART::stop( void )
{
  reset();

  context.digitalA.setMode( Port::InPU );
  context.digitalB.setMode( Port::InPU );
  context.digitalA.set();
  context.digitalB.set();
}

//-------------------------------------------------------------------
void SensorUART::update( void )
{
  BYTE c;
  BYTE ident;
  WORD msg;
  WORD cmd;
  BYTE len;
  BYTE lenExp;
  bool ok = true;

  c = nextSample();

  if( skip_IR_Error && skip_IR_Error != c )
    return;

  skip_IR_Error = 0;

  lenExp =  (c>>3) & 0x07;
  len = 1<< lenExp; //getLength(c);

  switch( state )
  {
    default:
    case 0:
        errCnt = 0;
        report.clrValid();

        if( c == CMD_TYPE )
        {
          if( read(0xff^c, 1) )
          {
            sensorType = buf[0];
            state = 1;
          }
        }
        break;

    case 1:
        msg = c & 0xC0;
        ident = 0;

        switch(msg)
        {
          case 0x00: // system message
            cmd = (WORD)c<<8;
            break;
          case 0x40: //command message
            cmd = (WORD)c<<8;
            break;
          case 0x80: //info  message
            ident = nextSample();
            cmd  = msg<<8;
            cmd |= ident;
            break;
          case 0xC0: //data message
            cmd = msg<<8;
            break;
          default:
            cmd = 0;
            state=1;
        }

        switch( cmd )
        {
          case 0x0400: // ACK
            sendByte(SYS_ACK);
            setBaudrate( p.speed );
            //sendByte(SYS_ACK();
            sendByte(SYS_NACK);
            state=2;
            break;

          case 0x4000:
            read(0xff^c, 1);
            break;

          case 0x4900:
            read(0xff^c, 2);
            break;

          case 0x5200:
            ok=read(0xff^c, 4);
            p.speed =    (DWORD)buf[0]
                      | ((DWORD)buf[1] << 8)
                      | ((DWORD)buf[2] << 16)
                      | ((DWORD)buf[3] << 24);
            break;

          case 0x8000:
            read(0xff^c^ident, len);
            break;

          case 0x8001:
            read(0xff^c^ident, 8);
            break;

          case 0x8002:
            read(0xff^c^ident, 8);
            break;

          case 0x8003:
            read(0xff^c^ident, len);
            if( sensorType == 33 )
            {
              skip_IR_Error = 0x90 | (c & 0x07);
            }
            break;

          case 0x8004:
            read(0xff^c^ident, 8);
            break;

          case 0x8080:
            read(0xff^c^ident, 4);
            break;

          default:
             errCnt++;
        }
        break;

        case 2:
          if( (c & 0xC0) == 0xC0 )
          {
            if( len <= 8)
            {
              ok=read(0xff^c, len);

              //---------------------------------------
              // EV3-Color-Sensor: wrong CRC in mode 4
              // workaround:
              if( sensorType == 29 && getMode(c)==4 && buf[7] == 2)
              {
                ok = true;
              }
              //---------------------------------------

              if(ok )
              {
                errCnt = 0;
                sendByte(SYS_NACK);

                report.rep.lenExp = lenExp;

                report.rep.value[0] =    (DWORD)buf[0]
                                      | ((DWORD)buf[1] << 8)
                                      | ((DWORD)buf[2] << 16)
                                      | ((DWORD)buf[3] << 24);
                // TODO: vorest nur max 8 Byte
                if( len > 4)
                {
                  report.rep.value[1] =    (DWORD)buf[4]
                                        | ((DWORD)buf[5] << 8)
                                        | ((DWORD)buf[6] << 16)
                                        | ((DWORD)buf[7] << 24);
                }

                report.setValid();
                report.rep.option = getMode(c) & 0x07;

                if( getMode(c) != currentMode )
                {
                  sendMode( currentMode ); // ???
                }
              }
            }
          }
          else
          {
            errCnt++;
          }
          break;
    } //switch( state )

  if( !ok )
    errCnt++;
  if( errCnt >10 )
  {
    state = 0;
    skip_IR_Error = 0;
    setBaudrate( 2400 );
  }
}

//-------------------------------------------------------------------
void SensorUART::reset( void )
{
  Properties p;
  this->p = p;
}

//-------------------------------------------------------------------
bool SensorUART::configMode( BYTE mode, WORD option )
{
  currentMode = mode;
  this->option = option;

  return( true );
}

//-------------------------------------------------------------------
bool SensorUART::sendMode( BYTE mode )
  {
  BYTE chk = 0xff ^ CMD_SELECT;
  chk ^= currentMode;
  uart.set(CMD_SELECT);
  uart.set(currentMode);
  uart.set(chk);

  BYTE cmd = nextSample();
  sendByte(SYS_NACK);
  return false;
}

//-------------------------------------------------------------------
BYTE SensorUART::nextSample()
{
  BYTE in = 0;

  Rtos::TimeOut uartTimeout( 500/*ms*/ );

  uartTimeout.start(); // autostart im konstruktor???

  while(!uartTimeout.timeout())
  {
    if( uart.get(in) ) //SensorUART.get() returns true, when new Byte arrives
    {
      return in;        //"in" is filled with new data by using the pointer &in
    }
  }
  return(0); // return 0 in case of a timeout to cause a SensorUART reset
}

//-------------------------------------------------------------------
bool  SensorUART::read( BYTE check, BYTE len )
{
  len = MIN( len, (BYTE)32 );
  for( BYTE i=0;i<len;i++)
  {
    buf[i] = nextSample();
    check ^= buf[i];
  }
  for( BYTE i=len;i<32;i++)
  {
    buf[i] = 0;
  }

  if( nextSample() != check )
  {
    return( false );
  }
  return( true );
}

//-------------------------------------------------------------------
void SensorUART::sendByte( BYTE msg )
{
  uart.set( msg );
}

//-------------------------------------------------------------------
void SensorUART::setBaudrate( float rate )
{
  Rtos::TimeOut timerLoc( 10 );

  while( !timerLoc.timeout() ) ;

  uart.setBaudrate(rate);
}

//EOF
