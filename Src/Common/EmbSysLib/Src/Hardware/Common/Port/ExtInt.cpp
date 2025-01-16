//*******************************************************************
/*!
\file   ExtInt.cpp
\author Thomas Breuer (Bonn-Rhein-Sieg University of Applied Sciences)
\date   23.03.2016

This file is released under the MIT License.
*/

//*******************************************************************
#include "ExtInt.h"

//*******************************************************************
//
// cHwExtInt
//
//*******************************************************************
//-------------------------------------------------------------------
//-------------------------------------------------------------------
void cHwExtInt::add( cHwExtInt::Task *ptr )
{
  isrList.add( ptr );
}

//-------------------------------------------------------------------
inline void cHwExtInt::isrHandler( void )
{
    Task *ptr = isrList.getFirst();
    while( ptr )
    {
        ptr->update();
        ptr = ptr->getNext();
    }
}
// EOF
