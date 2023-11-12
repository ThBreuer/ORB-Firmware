//*******************************************************************
/*!
\file   Rtos.cpp
\author Thomas Breuer (Bonn-Rhein-Sieg University of Applied Sciences)
\date   13.03.2023

License: See file "LICENSE"
*/

//*******************************************************************
#include "Rtos.h"
#include "Std/Report.h"
#include "Module/ReportID_Mod.h"

//*******************************************************************
namespace EmbSysLib {
namespace Mod {

using namespace Std;

//*******************************************************************
//
// Rtos
//
//*******************************************************************
//-------------------------------------------------------------------
Rtos *Rtos::ptr = NULL;

}  } //namespace

//*******************************************************************
//
// Rtos::Timer
//
//*******************************************************************
//-------------------------------------------------------------------
Rtos::TimeOut::TimeOut( //Rtos &taskHandlerIn,
                            WORD          timeToWait_msec,
                            WORD          timeToWait_usec )

//: taskHandler( taskHandlerIn )

{
  set( timeToWait_msec, timeToWait_usec ); // Don't use cTimer constructor
}

//-------------------------------------------------------------------
DWORD Rtos::TimeOut::getTics( void )
{
  return( Rtos_Mcu::getTics() );
}

//-------------------------------------------------------------------
DWORD Rtos::TimeOut::getTimeOfTic( void )
{
  return( Rtos_Mcu::getTimeOfTic() );
}

//EOF
