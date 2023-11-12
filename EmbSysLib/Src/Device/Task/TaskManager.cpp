//*******************************************************************
/*!
\file   TaskManager.cpp
\author Thomas Breuer (Bonn-Rhein-Sieg University of Applied Sciences)
\date   31.01.2023

License: See file "LICENSE"
*/

//*******************************************************************
#include "TaskManager.h"

//*******************************************************************
namespace EmbSysLib {
namespace Dev {

//*******************************************************************
//
// TaskManager
//
//*******************************************************************
//-------------------------------------------------------------------
//
// nothing to do ...
//
//*******************************************************************
//
// TaskManager::Timer
//
//*******************************************************************
//-------------------------------------------------------------------
TaskManager::TimeOut::TimeOut( TaskManager &taskHandlerIn,
                            WORD          timeToWait_msec,
                            WORD          timeToWait_usec )

: taskHandler( taskHandlerIn )

{
  set( timeToWait_msec, timeToWait_usec ); // Don't use cTimer constructor
}

//-------------------------------------------------------------------
DWORD TaskManager::TimeOut::getTics( void )
{
  return( taskHandler.locTask.tic /*getTics()*/ );
}

//-------------------------------------------------------------------
DWORD TaskManager::TimeOut::getTimeOfTic( void )
{
  return( taskHandler.getCycleTime() );
}

} } //namespace

//EOF
