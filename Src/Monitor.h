//*******************************************************************
/*!
\file   Monitor.h
\author Thomas Breuer (Bonn-Rhein-Sieg University of Applied Sciences)
\date   03.02.2021
*/

//*******************************************************************
#ifndef _MONITOR_H
#define _MONITOR_H

//*******************************************************************
#include "lib.h"
#include "Common/Properties.h"

//*******************************************************************
/*!
\class Monitor
\brief
*/
class Monitor
{
  public:
    //---------------------------------------------------------------
    Monitor();

    void clear();

    void getNextLine(cMonitorFromORB::Data &out);

    void printf(BYTE line,const char *format, va_list va);

    static void printConsole( const char *str );

  private:
    //---------------------------------------------------------------
    char text[4][31];

    static Fifo<char> fifo;
    BYTE   line = 0;
    bool   isLastFifo = false;
};

#endif
