//*******************************************************************
/*!
\file   BT_RN41.h
\author Thomas Breuer (Bonn-Rhein-Sieg University of Applied Sciences)
\date   03.02.2021
*/

//*******************************************************************
#include "Bluetooth/Bluetooth.h"

//*******************************************************************
/*!
\class
\brief
*/
class BT_RN41 : public Bluetooth
{
  public:
    //---------------------------------------------------------------
    BT_RN41( cHwUART_Ext  &_uart )
    : Bluetooth(_uart)
    {
    }

    //---------------------------------------------------------------
    bool waitForAckn(const char *str)
    {
      BYTE c;
      char buf[8];
      BYTE pos = 0;
      unsigned timeout = 100000;

      while( pos < 7 && timeout-- )
      {
        System::delayMicroSec(1);
        if( uart.get(c) )
        {
          if( strcmp(str,buf) == 0 )
          {
            return( true );
          }
          buf[pos++] = c;
          buf[pos  ] = 0;
        }
      }
      return( false );
    }

    //---------------------------------------------------------------
    void config(const char *name)
    {
      char str[32];
      sprintf(str,"SN,%-16.16s\r", name);

      // TODO: capture error event
      send("$$$");   // enter command mode
      if( waitForAckn("CMD") == false )
      {
        uart.setBaudrate(115200);
        send("$$$");   // enter command mode
        waitForAckn("CMD");
      //  send("SU,46\r");
        send("SU,11\r");
        waitForAckn("AOK");
        send("R,1\r");   // reboot
        //System::delayMilliSec(1000);
        //uart.setBaudrate(460800);
        //System::delayMilliSec(1000);
        send("$$$");   // enter command mode
        waitForAckn("CMD");
      }
      send(str);       // set name
      waitForAckn("AOK");
      send("R,1\r");   // reboot
    }

};
