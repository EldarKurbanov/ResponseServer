//
// Created by mrkotyk on 05.08.2019.
//

#ifndef RESPONSESERVER_CONTROL_HARDWARE_H
#define RESPONSESERVER_CONTROL_HARDWARE_H

#include <wiringPi.h>

void control_hardware_init();

void set_pins(int v0,  int v1,  int v2,  int v3,  int v4,  int v5,  int v6,
              int v7,  int v8,  int v9,  int v10, int v11, int v12, int v13,
              int v14, int v15, int v16, int v17, int v18, int v19, int v20);

void set_pins_arr(int* arr, int n);

void forward() {

}

#endif //RESPONSESERVER_CONTROL_HARDWARE_H
