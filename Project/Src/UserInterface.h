//*******************************************************************
/*!
\file   UserInterface.h
\author Thomas Breuer (Bonn-Rhein-Sieg University of Applied Sciences)
\date   03.02.2021
*/

//*******************************************************************
#ifndef _USER_INTERFACE_H
#define _USER_INTERFACE_H

//*******************************************************************
#include "lib.h"
#include "Settings.h"
#include "AppTask.h"

//*******************************************************************
/*!
\class UserInterface
\brief
*/
class UserInterface
{
  public:
    //---------------------------------------------------------------
    UserInterface( TaskManager &taskHandler,
                   AppTask      &app,
                   Settings     &settings );

    //---------------------------------------------------------------
    void update();

    //---------------------------------------------------------------
    void startApp( BYTE param );

    //---------------------------------------------------------------
    void stopApp();

    //---------------------------------------------------------------
    bool isAppActive();

    //---------------------------------------------------------------
    void setMonitorEvent( BYTE event );

    //-------------------------------------------------------------------
    void setVcc( BYTE Vcc );

  private:
    //---------------------------------------------------------------
    TaskManager::TimeOut  btnTimer;

    Settings            &settings;
    AppTask             &app;
};

#endif
