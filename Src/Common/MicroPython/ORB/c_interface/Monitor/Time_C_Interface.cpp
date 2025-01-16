#include "Time_C_Interface.h"
#include "stdint.h"
#include "stdio.h"

#include "EmbSysLib.h"

long int offs = GetSysTimeMilliSec();

extern "C" {

uint32_t getTime(){
//    printf("getTime()\n");
    return GetSysTimeMilliSec()-offs;
}

void wait(uint32_t time){
//    printf("wait(%d)", time);
    /// todo
//    DWORD timeToGo = getTime()+time;
//    do
//    {
//      Sleep(1);
//    }  while( getTime() < timeToGo);

    Sleep( time );
}

}
