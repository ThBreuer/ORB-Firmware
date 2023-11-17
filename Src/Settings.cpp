//*******************************************************************
/*!
\file   Settings.cpp
\author Thomas Breuer (Bonn-Rhein-Sieg University of Applied Sciences)
\date   03.02.2021
*/

//*******************************************************************
#include "lib.h"
#include "Settings.h"

//*******************************************************************
//
// Settings
//
//*******************************************************************
//-------------------------------------------------------------------
Settings::Settings( Memory &_mem )
: mem(_mem)
{
}

//-------------------------------------------------------------------
BYTE Settings::getVccLevelLow( void )
{
  return( mem.data.VCC_low );
}

//-------------------------------------------------------------------
BYTE Settings::getVccLevelOK( void )
{
  return( mem.data.VCC_ok );
}

//-------------------------------------------------------------------
void Settings::get( cSettingsFromORB::Data &out )
{
  strncpy( out.name, mem.data.name, 20 );
  out.VCC_ok  = mem.data.VCC_ok;
  out.VCC_low = mem.data.VCC_low;
}

//-------------------------------------------------------------------
void Settings::store( cSettingsToORB::Data &in )
{
  strncpy( mem.data.name, in.name, 20 );
  mem.data.VCC_ok  = in.VCC_ok;
  mem.data.VCC_low = in.VCC_low;
  mem.store();
}

//EOF
