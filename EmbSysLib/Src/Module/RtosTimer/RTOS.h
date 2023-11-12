//*******************************************************************
/*!
\file   Module/RTOS/RTOS.h
\author Thomas Breuer
\date   17.12.2014, 09.03.2016
*/

//*******************************************************************
#ifndef _RTOS_H
#define _RTOS_H

//*******************************************************************
#include "lib.h"

//*******************************************************************
/*!
\class cRTOS

\brief Interface to the real time operating system (RTOS)

\todo Add description

\example cRTOS.cpp
*/
class cRTOS
{
  public:

  public:
    //***************************************************************
    /*!
    \class Timer

    \brief Implements a RTOS timer
    \see cTimer
    \example cRTOS.cpp

    \todo An automatic restart of the timer within timeout() fails, if
          a Task is stopped and restarted. Reason: timeToGo is NOT
          recalculated. timer.start() MUST be used OR NO auto restart!
    */
    class Timer : public cTimer
    {
      public:
        //-----------------------------------------------------------
        /*! Instantiate a timer

            The runtime will be stored in the object. Further calls to
            \a start() or \a timeout() without parameter will use this
            stored runtime.
            \param timeToWait_msec Runtime in miliseconds (ms)
        */
        Timer( WORD timeToWait_msec = 0);

      private:
        //---------------------------------------------------------------
        virtual DWORD getTics();

        //---------------------------------------------------------------
        virtual DWORD getTimeOfTic();

    }; //RTOS::Timer

  public:
    //---------------------------------------------------------------
    /*! Instatiate a RTOS

        Setup RTOS and init RTOS related hardware (system tic
        interrupt,...)
    */
    cRTOS( void );

}; //cRTOS

#endif
