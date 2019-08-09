//
// Created by mrkotyk on 05.08.2019.
//
#include "control_hardware.h"

void control_init() {
    if(wiringPiSetup() != 0)
        err_exit("<control_hardware_setup> can't setup wiringPi.");

    control_hardware_setup_pins();
}

void control_hardware_setup_pins() {
    pinMode(0, OUTPUT);
}

void control_hardware_forward(unsigned int how_long) {
    digitalWrite (0, 1) ;  // On
    delay (how_long) ;                // mS
    digitalWrite (0, 0) ;  // Off
}



