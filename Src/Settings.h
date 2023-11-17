//*******************************************************************
/*!
\file   Settings.h
\author Thomas Breuer (Bonn-Rhein-Sieg University of Applied Sciences)
\date   03.02.2021
*/

//*******************************************************************
#ifndef _SETTINGS_H
#define _SETTINGS_H

//*******************************************************************
#include "lib.h"
#include "Properties.h"

//*******************************************************************
/*!
\class Settings
\brief
*/
class Settings
{
  public:
    //---------------------------------------------------------------
    Settings( Memory &mem );

    //---------------------------------------------------------------
    void get( cSettingsFromORB::Data &out);

    //---------------------------------------------------------------
    BYTE getVccLevelLow( void );

    //---------------------------------------------------------------
    BYTE getVccLevelOK( void );

    //---------------------------------------------------------------
    void store( cSettingsToORB::Data &in);

  private:
    //---------------------------------------------------------------
    cDevMemoryFlash<cSettingsToORB::Data> mem;

};

#endif
