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

Fifo<char> Monitor::fifo(255);

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
  if( fifo.isEmpty() || isLastFifo ) // nur jedes 2. Mal an Console
  {
    line = (line>=3)?0:line+1;
    out.line = line;
    strncpy( out.text, text[line],30);
    isLastFifo = false;
  }
  else
  {
    BYTE i = 0;
    char c;
    while( i < 30 && fifo >> c ) // todo check out.text memory size, is it = 31?
    {
      out.text[i++] = c;
    }
    out.line = 0xFF;
    out.text[i] = 0;
    isLastFifo = true;
  }
}

//-------------------------------------------------------------------
void Monitor::printf(BYTE line,const char *format, va_list va)
{
  if( line < 4 )
    vsnprintf( text[line], 31, format, va );
}

//-------------------------------------------------------------------
void Monitor::printConsole( const char *str )
{
    // todo funktion wird u.u. schneller aufgerufen, als fifo geleert werden kann.
    // Auf leere fifo warten geht auch nicht, da monitor ggf. nicht da.
    // Abhilfe: RTOS.pause???
    System::delayMilliSec(2);
    while( *str )
    {
      while( !(fifo << *str) )
      {
        char dummy;
        fifo >> dummy;
      }
      str++;
    }
}

//EOF
