//*******************************************************************
/*!
\author Nils Hoffmann
\date   12.10.2024
*/

#include "Sensor_C_Interface.h"

#include "Daten.h"

extern Daten            daten;

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdint.h>

void configSensor (uint8_t port,uint8_t t,uint8_t m,uint16_t o) {
    //printf("Sensor port:%d type:%d mode:%d offset:%d\n",port ,t ,m ,o);
    if( port < 4)
    {
      Daten::ConfigToORB::Data conf = daten.config.d.data;

      conf.sensor[port].type = t;
      conf.sensor[port].mode = m;
      conf.sensor[port].option = o;
      daten.config << conf;
    }
}

//static sensor_return_values values = {.value={0,0},.type=0,.option=0,.lenExp=0};

void getSensor(uint8_t port, sensor_return_values* values){

  if( port < 4 )
  {
    Daten::PropFromORB::Data::Sensor &s = daten.mess.d.data.sensor[port];

    values->value[0] = s.value[0];
    values->value[1] = s.value[1];
    values->type     = s.type;
    values->option   = s.option;
    values->lenExp   = 0; // ???
  }
}

uint32_t getSensorValueExt(uint8_t id, uint8_t ch ) {
    // ORB-Monitor does not support VlueExt
    return 0;
}

uint8_t getSensorDigital (uint8_t id) {
    if( id < 2 )
    {
      return( daten.mess.d.data.taster[id] );
    }
    return false;
}

#ifdef __cplusplus
}
#endif

