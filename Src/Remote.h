//*******************************************************************
/*!
\file   Remote.h
\author Thomas Breuer (Bonn-Rhein-Sieg University of Applied Sciences)
\date   03.02.2021
*/

//*******************************************************************
#ifndef _REMOTE_H
#define _REMOTE_H

//*******************************************************************
#include "lib.h"
#include "Module/Download.h"
#include "Module/Rtos/Rtos.h"

//-------------------------------------------------------------------
#include "Settings.h"
#include "UserInterface.h"
#include "Control.h"
#include "ORBlocal.h"
#include "MotorTask.h"
#include "SensorTask.h"

//*******************************************************************
/*!
\class Remote
\brief
*/
class Remote
{
  private:
    //***************************************************************
    /*!
    \class DownloadInterf
    \brief
    */
    class DownloadInterf : public cDownload::Interface
    {
      public:
        //-----------------------------------------------------------
        DownloadInterf( cDownload     &download,
                        Memory     &mem,
                        UserInterface &ui )

        : cDownload::Interface( download, mem )
         ,ui(ui)
        {
        }

        //-----------------------------------------------------------
        virtual bool onStart()
        {
          ui.stopApp();
          return( true );
        }

        //-----------------------------------------------------------
        virtual void onReady()
        {
        }

        UserInterface &ui;
    };

  public:
    //---------------------------------------------------------------
    Remote( cISC          &ipc,
            UserInterface &ui,
            Control       &ctrl,
            Settings      &settings,
            Monitor       &monitor );

    //---------------------------------------------------------------
    void update();

  private:
    //---------------------------------------------------------------
    cISC           &ipc;
    UserInterface  &ui;
    Control        &ctrl;
    Settings       &settings;
    Monitor        &monitor;

    cISC::Data<cConfigToORB,     0> configIn;
    cISC::Data<cPropToORB,       1> propIn;
    cISC::Data<cPropFromORB,     2> propOut;
    cISC::Data<cMonitorToORB,    3> monitorIn;
    cISC::Data<cMonitorFromORB,  4> monitorOut;
    cISC::Data<cSettingsFromORB, 5> settingsOut;
    cISC::Data<cSettingsToORB,   6> settingsIn;

    cDownload        download;
    DownloadInterf   interface0;
    //DownloadInterf   interface1;
    //DownloadInterf   interface2;

    bool configReceivedFlag;

    ORB::Sensor report[NUM_OF_SENSOR_PORTS];

    bool acceptFlag;

};

#endif
