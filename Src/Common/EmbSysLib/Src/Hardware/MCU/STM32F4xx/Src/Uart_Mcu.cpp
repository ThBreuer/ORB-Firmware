//*******************************************************************
/*!
\file   Uart_Mcu.cpp
\author Thomas Breuer (Bonn-Rhein-Sieg University of Applied Sciences)
\date   16.10.2022

License: See file "LICENSE"
*/

//*******************************************************************
#include "Uart_Mcu.h"
#include "PinConfig.h"
#include "Std/Report.h"
#include "Hardware/ReportID_Hw.h"

//*******************************************************************
namespace EmbSysLib {
namespace Hw {

//*******************************************************************
//
// Uart_Mcu
//
//*******************************************************************
//-------------------------------------------------------------------
#if ( system_PCLK_UART != 42000000 )
  #error "system_PCLK_UART not defined or wrong value"
#endif

//-------------------------------------------------------------------
Uart_Mcu *Uart_Mcu::uartPtr_1 = 0;
Uart_Mcu *Uart_Mcu::uartPtr_2 = 0;
Uart_Mcu *Uart_Mcu::uartPtr_3 = 0;
Uart_Mcu *Uart_Mcu::uartPtr_4 = 0;
Uart_Mcu *Uart_Mcu::uartPtr_5 = 0;
Uart_Mcu *Uart_Mcu::uartPtr_6 = 0;

//-------------------------------------------------------------------
Uart_Mcu::Uart_Mcu( USART_Id id,
                    DWORD    baud,
                    BYTE     mode,
                    WORD     sizeRxBuf,
                    WORD     sizeTxBuf )

: Uart( ReportID_Hw::Module::UART_MCU, sizeRxBuf, sizeTxBuf )
{
  switch( id )
  {
    case USART_1:
      ptr           = (USART_TypeDef*)USART1_BASE;
      uartPtr_1     = this;
      dmaStream     = DMA2_Stream2;
      dmaChannel    = 4;

      RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
      RCC->AHB1ENR |= RCC_AHB1ENR_DMA2EN;

      PinConfig::set( PinConfig::USART1_RX, PinConfig::ALTERNATE_FUNC );
      PinConfig::set( PinConfig::USART1_TX, PinConfig::ALTERNATE_FUNC );
      if( mode & RTS )
      {
        PinConfig::set( PinConfig::USART1_RTS, PinConfig::ALTERNATE_FUNC );
      }
      if( mode & CTS )
      {
        PinConfig::set( PinConfig::USART1_CTS, PinConfig::ALTERNATE_FUNC );
      }
      NVIC_EnableIRQ( USART1_IRQn );
      break;

  case USART_2:
      ptr           = (USART_TypeDef*)USART2_BASE;
      uartPtr_2     = this;
      dmaStream     = DMA1_Stream5;
      dmaChannel    = 4;

      RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
      RCC->AHB1ENR |= RCC_AHB1ENR_DMA1EN;

      PinConfig::set( PinConfig::USART2_RX, PinConfig::ALTERNATE_FUNC );
      PinConfig::set( PinConfig::USART2_TX, PinConfig::ALTERNATE_FUNC );
      if( mode & RTS )
      {
        PinConfig::set( PinConfig::USART2_RTS, PinConfig::ALTERNATE_FUNC );
      }
      if( mode & CTS )
      {
        PinConfig::set( PinConfig::USART2_CTS, PinConfig::ALTERNATE_FUNC );
      }
      NVIC_EnableIRQ( USART2_IRQn );
      break;

    case USART_3:
      ptr           = (USART_TypeDef*)USART3_BASE;
      uartPtr_3     = this;
      dmaStream     = DMA1_Stream1;
      dmaChannel    = 4;

      RCC->APB1ENR |= RCC_APB1ENR_USART3EN;
      RCC->AHB1ENR |= RCC_AHB1ENR_DMA1EN;

      PinConfig::set( PinConfig::USART3_RX, PinConfig::ALTERNATE_FUNC |PinConfig::HIGH_SPEED);
      PinConfig::set( PinConfig::USART3_TX, PinConfig::ALTERNATE_FUNC |PinConfig::HIGH_SPEED);
      if( mode & RTS )
      {
        PinConfig::set( PinConfig::USART3_RTS, PinConfig::ALTERNATE_FUNC );//| PinConfig::PULL_UP );
      }
      if( mode & CTS )
      {
        PinConfig::set( PinConfig::USART3_CTS, PinConfig::ALTERNATE_FUNC ); // );
      }
      NVIC_EnableIRQ( USART3_IRQn );
      break;

    case UART_4:
      ptr           = (USART_TypeDef*)UART4_BASE;
      uartPtr_4     = this;
      dmaStream     = DMA1_Stream2;
      dmaChannel    = 4;

      RCC->APB1ENR |= RCC_APB1ENR_UART4EN;
      RCC->AHB1ENR |= RCC_AHB1ENR_DMA1EN;

      PinConfig::set( PinConfig::UART4_RX, PinConfig::ALTERNATE_FUNC );
      PinConfig::set( PinConfig::UART4_TX, PinConfig::ALTERNATE_FUNC );
      // no RTS/CTS
      NVIC_EnableIRQ( UART4_IRQn );
      break;

    case UART_5:
      ptr           = (USART_TypeDef*)UART5_BASE;
      uartPtr_5     = this;
      dmaStream     = DMA1_Stream0;
      dmaChannel    = 4;

      RCC->APB1ENR |= RCC_APB1ENR_UART5EN;
      RCC->AHB1ENR |= RCC_AHB1ENR_DMA1EN;

      PinConfig::set( PinConfig::UART5_RX, PinConfig::ALTERNATE_FUNC );
      PinConfig::set( PinConfig::UART5_TX, PinConfig::ALTERNATE_FUNC );
      // no RTS/CTS
      NVIC_EnableIRQ( UART5_IRQn );
      break;

    case USART_6:
      ptr           = (USART_TypeDef*)USART6_BASE;
      uartPtr_6     = this;
      dmaStream     = DMA2_Stream1;
      dmaChannel    = 5;

      RCC->APB2ENR |= RCC_APB2ENR_USART6EN;
      RCC->AHB1ENR |= RCC_AHB1ENR_DMA2EN;

      PinConfig::set( PinConfig::USART6_RX, PinConfig::ALTERNATE_FUNC );
      PinConfig::set( PinConfig::USART6_TX, PinConfig::ALTERNATE_FUNC );
      if( mode & RTS )
      {
        PinConfig::set( PinConfig::USART6_RTS, PinConfig::ALTERNATE_FUNC );
      }
      if( mode & CTS )
      {
        PinConfig::set( PinConfig::USART6_CTS, PinConfig::ALTERNATE_FUNC );
      }
      NVIC_EnableIRQ( USART6_IRQn );
      break;

    default:
      report.error( ReportID_Hw::Event::WRONG_ID );
      break;

  }

  // DMA setting
  memset(dataRxBuf.speicher,0,dataRxBuf.size);

  RCC->AHB1ENR |= RCC_AHB1ENR_DMA1EN;
  dmaStream->CR   =   (dmaChannel<<25) // channel
                       | DMA_SxCR_MINC
                       | DMA_SxCR_CIRC;
  dmaStream->NDTR = dataRxBuf.size;
  dmaStream->PAR  = (DWORD)&ptr->DR;
  dmaStream->M0AR = (DWORD)dataRxBuf.speicher;
  dmaStream->M1AR = 0;
  //DMA1_Stream1->FCR  =;

  dmaStream->CR   |=   DMA_SxCR_EN;


//  ptr->CR2 |=  ((mode&STOPBIT2)?(MTYPE)2<<12:0); // 1 or 2  stop bit
  ptr->CR2 |=  (MTYPE)0<<12; // 1 or 2  stop bit

  ptr->CR3 |=  (  ((mode&RTS)?USART_CR3_RTSE:0)
                | ((mode&CTS)?USART_CR3_CTSE:0)
                | USART_CR3_ONEBIT ); // set hardware flow control

  setBaudrate( baud );

  ptr->CR3 |= USART_CR3_DMAR;

  ptr->CR1 |= (  USART_CR1_UE       // Enable USART
               | USART_CR1_TCIE     // Transm. complete interr. enable
              // | USART_CR1_RXNEIE // Receive reg. not empty interr. enable
               | ((mode&(EVEN|ODD))?USART_CR1_M  :0)  // 8+paritry = 9 Bit
               |  ((mode&(EVEN|ODD))?USART_CR1_PCE:0)  //  parity
               |  ((mode&      ODD )?USART_CR1_PS :0)  // 0: even
              );

  ptr->CR1 |=  (     USART_CR1_RE   // RX mode
                     |  USART_CR1_TE );// TX mode

}

//-------------------------------------------------------------------
inline BYTE Uart_Mcu::getByte( void )
{
  return( ptr->DR );
}

//-------------------------------------------------------------------
inline void Uart_Mcu::setByte( BYTE c )
{
  ptr->DR = c;
}

//-------------------------------------------------------------------
// Configure the USART Baud Rate:
//
// OVER8==0:
//   BRR: mmmm mmmm mmmm ffff
//   div: Fixpoint number = M+F/16
//
//            fck                         fck
//   div = ---------  =>  BRR = 16*div = ------
//         16 x baud                      baud
//
void Uart_Mcu::setBaudrate( DWORD baud )
{
  if( baud > 1000000 ) //150000)
  {
    DWORD brr = (WORD)((float)2*system_PCLK_UART / baud +0.5);
    ptr->BRR  = (brr&0XFFF0) | ((brr>>1)&0x0007);
    ptr->CR1 |= USART_CR1_OVER8;
  }
  else
  {
    DWORD brr = (WORD)((float)system_PCLK_UART / baud +0.5);
    ptr->BRR  = brr;
    ptr->CR1 &= ~USART_CR1_OVER8;
  }
}

//-------------------------------------------------------------------
void Uart_Mcu::isr( void )
{
System::disableInterrupt();

  DWORD sr = ptr->SR;
///not USART 3
/*
  if( sr & (USART_SR_RXNE) )// Receive data register not empty
  {
    isrRx();
  }
  if( sr & USART_SR_ORE )// Receive data register not empty
  {
    isrRx();
  }
*/
  if( ptr->SR  & USART_SR_TC ) // Transmission complete?
  {
//      while( !(ptr->SR & USART_SR_TXE) )
//      {
//        asm("NOP");
//      }

    isrTx();
    ptr->SR &= ~( USART_SR_TC); // reset per sw because DR not set if fifo empty
  }
System::enableInterrupt();

}

//#############################
//-------------------------------------------------------------------
bool Uart_Mcu::get( BYTE &data )
{
  BYTE tmp = 0;

    //---------------------------------------------------------------
    /*! Read an object from FIFO
        \param ref Referenc to an object
        \return
                - true, if succeeded
                - false, if FIFO is empty, no object read
    */

      bool ret = false;

      //Hw::System::disableInterrupt();
      WORD in = (dataRxBuf.size - dmaStream->NDTR);

      if( dataRxBuf.out != in )
      {
        data = dataRxBuf.speicher[dataRxBuf.out];
        dataRxBuf.out = (dataRxBuf.out < dataRxBuf.size-1) ? dataRxBuf.out+1 : 0;
        //anz--;
        ret = true;
      }
      //Hw::System::enableInterrupt();

      return( ret );
}
//#############################


//-------------------------------------------------------------------
extern "C"
{
  void USART1_IRQHandler(void)
  {
    Uart_Mcu::uartPtr_1->isr();
  }
}

//-------------------------------------------------------------------
extern "C"
{
  void USART2_IRQHandler(void)
  {
    Uart_Mcu::uartPtr_2->isr();
  }
}

//-------------------------------------------------------------------
extern "C"
{
  void USART3_IRQHandler(void)
  {
    Uart_Mcu::uartPtr_3->isr();
  }
}

//-------------------------------------------------------------------
extern "C"
{
  void UART4_IRQHandler(void)
  {
    Uart_Mcu::uartPtr_4->isr();
  }
}

//-------------------------------------------------------------------
extern "C"
{
  void UART5_IRQHandler(void)
  {
    Uart_Mcu::uartPtr_5->isr();
  }
}

//-------------------------------------------------------------------
extern "C"
{
  void USART6_IRQHandler(void)
  {
    Uart_Mcu::uartPtr_6->isr();
  }
}

}  } //namespace

//EOF
