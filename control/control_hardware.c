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
    pinMode(7, OUTPUT);
    pinMode(0, OUTPUT);
    pinMode(2, OUTPUT);
    pinMode(3, OUTPUT);
}

void control_forward() {
    printf("forward\n");
    digitalWrite (7, 1) ;  // On
    delay (DELAY_TIME);
    digitalWrite (7, 0) ;  // Off
}

void control_back() {
    printf("back\n");
    digitalWrite (0, 1) ;  // On
    delay (DELAY_TIME);
    digitalWrite (0, 0) ;  // Off
}

void control_rotate_left() {
    printf("rotate left\n");
    digitalWrite (2, 1) ;  // On
    delay (DELAY_TIME);
    digitalWrite (2, 0) ;  // Off
}

void control_rotate_right() {
    printf("rotate right\n");
    digitalWrite (3, 1) ;  // On
    delay (DELAY_TIME);
    digitalWrite (3, 0) ;  // Off
}

void control_left_forward() {

}

void control_right_forward() {

}



