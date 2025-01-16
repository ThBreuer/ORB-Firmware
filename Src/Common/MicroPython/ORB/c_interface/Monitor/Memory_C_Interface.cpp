#include <stdio.h>
#include <stdint.h>

#include "EmbSysLib.h"

Memory_Mcu mem( "mem.bin", 128L*1024 );


extern "C" {


    void clearMemory(){
         //printf("clearMemory()\n");
         mem.erase();
    }

    void setMemory(uint32_t addr, uint8_t *data, uint32_t data_size){
        //printf("Writing to adrr(%d)\n", addr);
        //for (uint8_t i = 0; i < data_size; i++) {
        //  printf("item: %d\n",data[i]);
        //}
        mem.unlock();
        for( DWORD i=0;i<data_size;i++)
          mem.write(addr++,data[i]);
        mem.lock();
    }

    void getMemory(uint32_t addr, uint8_t* data, uint32_t data_size){
      

        for (uint8_t i = 0; i < data_size; i++) {
            data[i] = mem.read(addr++);
        }
    }

}
