//*******************************************************************
/*!
\file   Module/ISC.cpp
\author Thomas Breuer
\date   09.02.2016

\brief  Summary of ISC classes (Inter system communication)
*/

//*******************************************************************
#include "Module/ISC/ISC.cpp"

#include "Module/ISC/ISC_UART.cpp"
//#include "Module/ISC/ISC_UDP.cpp"
#ifdef MCU_VIRTUAL
 #ifdef USB_ON
 #include "Module/ISC/ISC_USBhost.cpp"
 #endif
#else
  #include "Module/ISC/ISC_USBdevice.cpp"
#endif

//EOF
