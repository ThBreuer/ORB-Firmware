//*******************************************************************
/*!
\file   UART_Ext.h
\author Thomas Breuer (Bonn-Rhein-Sieg University of Applied Sciences)
\date   12.03.2016
*/

//*******************************************************************
#ifndef _HW_UART_EXT_H
#define _HW_UART_EXT_H

//*******************************************************************
#include "Hardware/Common/Uart/Uart.h"

//-------------------------------------------------------------------
#if ( system_PCLK_UART != 42000000 )
  #error "system_PCLK_UART not defined or wrong value"
#endif

//*******************************************************************
/*!
\class cHwUART_Ext
\brief
*/
class cHwUART_Ext : public Uart_Mcu
{
  public:
    //---------------------------------------------------------------
    cHwUART_Ext( USART_Id id,
                 DWORD    baud,
                 BYTE mode,
                 WORD     sizeRxBuf,
                 WORD     sizeTxBuf )

    : Uart_Mcu::Uart_Mcu( id, baud, mode, sizeRxBuf, sizeTxBuf )

    {
      usartId = id;
    }

//    //---------------------------------------------------------------
//    void setBaudrate(float baudRate)
//    {
//      if( baudRate > 1500)
//      {
//        DWORD brr = (WORD)(2.0*system_PCLK_UART / baudRate);
//        ptr->BRR  = (brr&0XFFF0) | ((brr>>1)&0x0007);
//        ptr->CR1 |= USART_CR1_OVER8;
//      }
//      else
//      {
//        DWORD brr = (WORD)(system_PCLK_UART / baudRate);
//        ptr->BRR  = brr;
//        ptr->CR1 &= ~USART_CR1_OVER8;
//      }
//    }

    //---------------------------------------------------------------
    void connectToPort()
    {
      // clean FIFO
      BYTE dummy;
      while( get( dummy ) );

      switch( usartId )
      {
        default:
          //error!
          break;

        case USART_1:
          PinConfig::set( PinConfig::USART1_RX );
          PinConfig::set( PinConfig::USART1_TX );
          break;

        case USART_2:
          PinConfig::set( PinConfig::USART2_RX );
          PinConfig::set( PinConfig::USART2_TX );
          break;

        case USART_3:
          PinConfig::set( PinConfig::USART3_RX );
          PinConfig::set( PinConfig::USART3_TX );
          break;

        case UART_4:
          PinConfig::set( PinConfig::UART4_RX );
          PinConfig::set( PinConfig::UART4_TX );
          break;

        case UART_5:
          PinConfig::set( PinConfig::UART5_RX );
          PinConfig::set( PinConfig::UART5_TX );
          break;

        case USART_6:
          PinConfig::set( PinConfig::USART6_RX );
          PinConfig::set( PinConfig::USART6_TX );
          break;
      }
    }

  private:
    //---------------------------------------------------------------
    USART_Id usartId;

}; //cHwUART_ext

#endif
