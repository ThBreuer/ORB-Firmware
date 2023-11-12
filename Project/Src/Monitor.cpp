//*******************************************************************
/*!
\file   Monitor.cpp
\author Thomas Breuer (Bonn-Rhein-Sieg University of Applied Sciences)
\date   03.02.2021
*/

//*******************************************************************
#include "lib.h"

//*******************************************************************
#include "Monitor.h"

//*******************************************************************
//
// Monitor
//
//*******************************************************************
//-------------------------------------------------------------------
Monitor::Monitor()
{
}

//-------------------------------------------------------------------
void Monitor::clear()
{
  for(int i=0;i<4;i++)
    ::strcpy(text[i],"");
}

//-------------------------------------------------------------------
void Monitor::getNextLine(cMonitorFromORB::Data &out)
{
  out.line = (out.line>=3)?0:out.line+1;
  strncpy( out.text, text[out.line],30);
}

//-------------------------------------------------------------------
void Monitor::printf(BYTE line,const char *format, va_list va)
{
  if( line < 4 )
    vsnprintf( text[line], 31, format, va );
}

//EOF
