//*******************************************************************
/*!
\author Nils Hoffmann
\date   12.10.2024
*/

#include "Monitor_C_Interface.h"
#include <stdio.h>
#include <stdint.h>

#include "Daten.h"

#ifdef __cplusplus
extern "C" {
#endif

extern Daten            daten;

uint8_t getMonitorKey(){
  Daten::MonitorToORB loc;
  // check monitorToORB.isTimeout / monitorToORB.isNew ???
  daten.monitorToORB >> loc;
	return loc.data.keycode;
}

void setMonitorText(uint8_t line, const char *str, size_t len)
{
	/*for(int i=0;i<len;i++)
        printf("%c", str[i]);*/ //this solution is slower but saves on heapspace

    /// todo printf if debug only
    //printf("%d:%.*s\n",line,(int)len, str);
    //printf("%d:%.*s\n",line,(int)len, str);
    //fflush(stdout);

    /// todo create and use methode
    if( 0 <= line && line < 4 )
    {
      if( len > 30 )
        len = 30;
      sprintf(daten.monitorFromORB.d.data.text[line],"%30s"," ");
      strncpy(daten.monitorFromORB.d.data.text[line],str,len+1);
      daten.monitorFromORB.setUpdate();
    }
}

#ifdef __cplusplus
}
#endif

