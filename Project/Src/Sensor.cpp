//*******************************************************************
/*!
\file   Sensor.cpp
\author Thomas Breuer (Bonn-Rhein-Sieg University of Applied Sciences)
\date   03.02.2021
*/

//*******************************************************************
#include "lib.h"
#include "Module/Rtos/Rtos.h"
#include "Sensor.h"

//*******************************************************************
//
// Sensor::Context
//
//*******************************************************************
//-------------------------------------------------------------------
Sensor::Context::Context( cDevAnalogIn &adc1_In,
                              cDevAnalogIn &adc2_In,
                              Port::Pin &digitalA_In,
                              Port::Pin &digitalB_In,
                              Port::Pin &digitalC_In,
                              Port::Pin &digitalD_In,
                              Port::Pin &digitalH_In )

  : adc1(adc1_In),
    adc2(adc2_In),
    digitalA(digitalA_In),
    digitalB(digitalB_In),
    digitalC(digitalC_In),
    digitalD(digitalD_In),
    digitalH(digitalH_In)

{
}

//*******************************************************************
//
// Sensor
//
//*******************************************************************
//-------------------------------------------------------------------
Sensor::Sensor( Sensor::Context &context_In )

  : context( context_In )
{
    context.digitalH.set();
    context.digitalH.setMode( Port::OutOD );
}

//EOF
