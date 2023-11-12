//*******************************************************************
/*!
\file   TaskManager.h
\author Thomas Breuer (Bonn-Rhein-Sieg University of Applied Sciences)
\date   31.01.2023

License: See file "LICENSE"
*/

//*******************************************************************
#ifndef _DEV_TASK_MANAGER_H
#define _DEV_TASK_MANAGER_H

//*******************************************************************
#include "Hardware/Common/Timer/Timer.h"

//*******************************************************************
namespace EmbSysLib {
namespace Dev {

//*******************************************************************
/*!
\class   TaskManager

\brief   Manages a list of tasks and calls their update() method

This base class contains an update-list, to which objects can be
added if derived from \a TaskManager::Task. The update()-methods of all
added objects are successively called by each timer interrupt.

\example DevTaskManager.cpp
*/
class TaskManager
{
  public:
    //*******************************************************************
    /*!
    \class Task
    \brief Base class for a Task
    */
    class Task : public Timer::Task
    {
      public:
        //---------------------------------------------------------
        /*! Method called by TaskManager.
            The application has to override this method.
        */
        virtual void update( void ) = 0;

    }; //class TaskManager::Task
    //*******************************************************************

  public:
    //*******************************************************************
    /*!
    \class Timer

    \brief Timing features within a task

    The timer uses the timer tics, which are provided by a task object.
    */
    class TimeOut : public cTimer
    {
      public:
        //---------------------------------------------------------------
        /*! Instantiate a timer
            The runtime will be stored in the object. Further calls to
            \a start() or \a timeout() without parameter will use this stored runtime.
            \param taskHandler Reference to a task handler, which
                               provides the timer tics
            \param timeToWait_msec Runtime in miliseconds (ms)
            \param timeToWait_usec Runtime in microseconds (us)
        */
        TimeOut( TaskManager &taskHandler,
               WORD          timeToWait_msec = 0,
               WORD          timeToWait_usec = 0 );

      private:
        //---------------------------------------------------------------
        virtual DWORD getTics( void );

        //---------------------------------------------------------------
        virtual DWORD getTimeOfTic( void );

      private:
        //---------------------------------------------------------------
        TaskManager &taskHandler;

    }; //TimeOut

  public:
    //---------------------------------------------------------------
    /*! Initialize a TaskManager
        \param timer Timer object
    */
    TaskManager( Timer &timer )
    : timer( timer )
    , locTask( *this )
    {
    }

  public:
    //---------------------------------------------------------------
    /*! Add a new object to the task list.
        The objects update()-method will be called periodically by
        a timer interrupt.
        \remark The update()-method of the TaskManager::Task may be
        called immediately, so call this add()-method only when the constructor of the Task-object is completed.
        \param ptr Pointer to the TaskManager::Task object
    */
    virtual void add( Task *ptr )
    {
      timer.add( ptr );
    }

    //---------------------------------------------------------------
    /*! Get cycle time of update() calls
        \return Cyycle in micro seconds (us)
    */
    virtual DWORD getCycleTime( void )
    {
      return( timer.getCycleTime() );
    }

  private:
    //---------------------------------------------------------------
    Timer &timer;

    class LocalTask : public Task
    {
   public:
    DWORD tic;
    LocalTask( TaskManager &tm)
    {
      tic = 0;
      tm.add( this);
    }

    void update()
    {
        tic++;
    }

    } locTask;

}; //class TaskManager

} } //namespace

#endif
