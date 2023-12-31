//*******************************************************************
/*!
\file   Encoder_MCU.cpp
\author Thomas Breuer (Bonn-Rhein-Sieg University of Applied Sciences)
\date   23.03.2016

This file is released under the MIT License.
*/

//*******************************************************************
#include "Encoder_MCU.h"

//*******************************************************************
//
// cHwEncoder_N
//
//*******************************************************************
//-------------------------------------------------------------------
cHwEncoder_N::cHwEncoder_N( TimerId timerId,
                            Mode    mode )

: cHwEncoder( mode )
{
  switch( timerId )
  {
    default:
      // error!
      break;

    case TIM_1:
      ptr           = TIM1;
      RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;

      PinConfig::set( PinConfig::TIM1_CH1 );
      PinConfig::set( PinConfig::TIM1_CH2 );
      break;

    case TIM_2:
      ptr           = TIM2;
      RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;

      PinConfig::set( PinConfig::TIM2_CH1 );
      PinConfig::set( PinConfig::TIM2_CH2 );
      break;

    case TIM_3:
      ptr           = TIM3;
      RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;

      PinConfig::set( PinConfig::TIM3_CH1 );
      PinConfig::set( PinConfig::TIM3_CH2 );
      break;

    case TIM_4:
      ptr           = TIM4;
      RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;

      PinConfig::set( PinConfig::TIM4_CH1 );
      PinConfig::set( PinConfig::TIM4_CH2 );
      break;

    case TIM_5:
      ptr           = TIM5;
      RCC->APB1ENR |= RCC_APB1ENR_TIM5EN;

      PinConfig::set( PinConfig::TIM5_CH1 );
      PinConfig::set( PinConfig::TIM5_CH2 );
      break;

  }

  ptr->CR1  = TIM_CR1_CEN;  // counter enable

  ptr->DIER = !TIM_DIER_UIE; // update interrupt enable
  ptr->EGR  = TIM_EGR_UG;   // re-initialize timer
  ptr->PSC  = 0;
  ptr->ARR  = 0xFFFF;

  ptr->SMCR &= ~(0x07<<0);
  ptr->SMCR |=  (0x03<<0); // Encode mode, both edges

  // \todo Check setting of CCER
  ptr->CCER  &= ~( (1<<1)
                  |(1<<5));

  if( mode & REVERSE )        // Input polarity
  {
    ptr->CCER  |=  (1<<1)    // CC1P
                  |(0<<5);   // CC2P
  }
  else // NORMAL
  {
    ptr->CCER  |=  (0<<1)    // CC1P
                  |(0<<5);   // CC2P
  }

  ptr->CNT = 0;
  cntLast  = 0;
}

//-------------------------------------------------------------------
int cHwEncoder_N::get( void )
{
  // warning: Do not change data types and/or casting!
  WORD  cnt = ptr->CNT;
  int   ret = (short int)(cnt - cntLast);

  cntLast = cnt;

  return( ret );
}

//EOF
