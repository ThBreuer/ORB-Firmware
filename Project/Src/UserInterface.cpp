//*******************************************************************
/*!
\file   UserInterface.cpp
\author Thomas Breuer (Bonn-Rhein-Sieg University of Applied Sciences)
\date   03.02.2021
*/

//*******************************************************************
#include "lib.h"
#include "UserInterface.h"

//*******************************************************************
extern Digital      ledUsr1;
extern Digital      ledUsr2;
extern Digital      btnUsr1;
extern Digital      btnUsr2;

extern DigitalIndicator pwrIndicator;

//*******************************************************************
//
// UserInterface
//
//*******************************************************************
//-------------------------------------------------------------------
UserInterface::UserInterface( TaskManager &taskHandler,
                              AppTask      &app,
                              Settings     &settings )

 : btnTimer( taskHandler, 20/*ms*/)
 , settings(settings)
 , app     ( app )

{
   //taskHandler.add( this );
}

//-------------------------------------------------------------------
void UserInterface::update()
{
  if( btnTimer.timeout() )
  {
    if( btnUsr1.getEvent() == Digital::ACTIVATED )
    {
      if( app.isRunning() )  stopApp();
      else                  startApp(0);
    }
    else if( btnUsr2.getEvent() == Digital::ACTIVATED )
    {
      if( app.isRunning() )  stopApp();
      else                  startApp(1);
    }
  }

  if( !app.isRunning() )
  {
     ledUsr1.clr();
     ledUsr2.clr();
  }
}

//-------------------------------------------------------------------
void UserInterface::startApp( BYTE param )
{
  if( !app.isRunning())
  {
    if( param )
      ledUsr2.set();
    else
      ledUsr1.set();
    app.Start(param);
  }
}

//-------------------------------------------------------------------
void UserInterface::stopApp()
{
  if( app.isRunning())
    app.stop();
}

//-------------------------------------------------------------------
bool UserInterface::isAppActive()
{
  return( app.isRunning() );
}

//-------------------------------------------------------------------
void UserInterface::setMonitorEvent( BYTE event )
{
  app.MonitorEvent = event;
}

//-------------------------------------------------------------------
void UserInterface::setVcc( BYTE Vcc )
{
  if     ( Vcc > settings.getVccLevelOK()  )  pwrIndicator.blink(1000, 90); //, 30);
  else if( Vcc > settings.getVccLevelLow() )  pwrIndicator.blink(1000, 80); //, 50);
  else                                        pwrIndicator.blink( 250, 30); //,100);
}
//EOF
