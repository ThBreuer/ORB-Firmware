#include "stdio.h"
#include "stdint.h"

#include "Daten.h"

extern Daten            daten;

extern "C" {

void setModelServo(uint8_t port, uint8_t speed, uint8_t angle){
    //printf("set servo(%d) speed(%d) angle(%d)\n", port, speed, angle);

    if( port < 2)
    {
      Daten::PropToORB::Data prop = daten.control.d.data;

      prop.modelServo[port].sspeed = speed;
      prop.modelServo[port].spos   = angle;

      daten.control << prop;
    }
}

}
