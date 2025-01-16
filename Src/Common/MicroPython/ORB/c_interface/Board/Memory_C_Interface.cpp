#include <stdio.h>
#include "AppTask.h"

extern "C" {

    void clearMemory(){
        AppTask::clearMemory(nullptr);
    }

    void setMemory(uint32_t addr, uint8_t *data, uint32_t data_size){
        AppTask::setMemory(nullptr, addr, data, data_size);
    }

    void getMemory(uint32_t addr, uint8_t* data, uint32_t data_size){
        AppTask::getMemory(nullptr, addr, data, data_size);
    }

}
