//*******************************************************************
/*!
\file   ORBlocal.h
\author Thomas Breuer (Bonn-Rhein-Sieg University of Applied Sciences)
\date   03.02.2021
\brief
*/

//*******************************************************************
#ifndef _ORB_LOCAL_H
#define _ORB_LOCAL_H

//*******************************************************************
#include "ORB.h"
#include <stdarg.h>

//*******************************************************************
#pragma pack(1)

//*******************************************************************
/*!
\class cORBlocal
\brief
*/
class cORBlocal : public ORB
{
  public:
    //-------------------------------------------------------
    void        (*funcPtr_configMotor       )(void *, BYTE, WORD, BYTE, BYTE, BYTE      );
    void        (*funcPtr_setMotor          )(void *, BYTE, BYTE, short, int            );
    ORB::Motor  (*funcPtr_getMotor          )(void *, BYTE                              );
    void        (*funcPtr_setModelServo     )(void *, BYTE, BYTE, BYTE                  );
    void        (*funcPtr_configSensor      )(void *, BYTE, BYTE, BYTE, WORD            );
    ORB::Sensor (*funcPtr_getSensor         )(void *, BYTE                              );
    WORD        (*funcPtr_getSensorValueExt )(void *, BYTE, BYTE                        );
    BYTE        (*funcPtr_getSensorDigital  )(void *, BYTE                              );
    void        (*funcPtr_setMonitorText    )(void *, BYTE, const char *, va_list       );
    int         (*funcPtr_getMonitorKey     )(void *                                    );
    DWORD       (*funcPtr_getTime           )(void *                                    );
    void        (*funcPtr_wait              )(void *, DWORD                             );
    void        (*funcPtr_clearMemory       )(void *                                    );
    void        (*funcPtr_setMemory         )(void *, DWORD addr, BYTE *data, DWORD size);
    void        (*funcPtr_getMemory         )(void *, DWORD addr, BYTE *data, DWORD size);

public:
    //-------------------------------------------------------
    virtual void        configMotor      (BYTE id,WORD t,BYTE a,BYTE Kp,BYTE Ki) {return(funcPtr_configMotor      (ptr,id,t,a,Kp,Ki));}
    virtual void        setMotor         (BYTE id,BYTE m, short s, int p       ) {return(funcPtr_setMotor         (ptr,id,m,s,p    ));}
    virtual ORB::Motor  getMotor         (BYTE id                              ) {return(funcPtr_getMotor         (ptr,id          ));}
    virtual void        setModelServo    (BYTE id, BYTE s, BYTE w              ) {return(funcPtr_setModelServo    (ptr,id,s,w      ));}
    virtual void        configSensor     (BYTE id,BYTE t,BYTE m,WORD o         ) {return(funcPtr_configSensor     (ptr,id,t,m,o    ));}
    virtual ORB::Sensor getSensor        (BYTE id                              ) {return(funcPtr_getSensor        (ptr,id          ));}
    virtual WORD        getSensorValueExt(BYTE id, BYTE ch                     ) {return(funcPtr_getSensorValueExt(ptr,id, ch      ));}
    virtual BYTE        getSensorDigital (BYTE id                              ) {return(funcPtr_getSensorDigital (ptr,id          ));}
    virtual void        setMonitorText   (BYTE line,const char *fmt, va_list va) {return(funcPtr_setMonitorText   (ptr,line,fmt,va ));}
    virtual BYTE        getMonitorKey    (                                     ) {return(funcPtr_getMonitorKey    (ptr             ));}
    virtual DWORD       getTime          (                                     ) {return(funcPtr_getTime          (ptr             ));}
    virtual void        wait             (DWORD time                           ) {return(funcPtr_wait             (ptr,time        ));}
    virtual void        clearMemory      (                                     ) {return(funcPtr_clearMemory      (ptr             ));}
    virtual void        setMemory        (DWORD addr, BYTE *data, DWORD s      ) {return(funcPtr_setMemory        (ptr,addr,data,s ));}
    virtual void        getMemory        (DWORD addr, BYTE *data, DWORD s      ) {return(funcPtr_getMemory        (ptr,addr,data,s ));}

    // TODO: implement getVcc()
    virtual float getVcc( void ) {return(0);}

    void *ptr;

};
#pragma pack()

#endif
