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
    pinMode(21, OUTPUT);
    pinMode(22, OUTPUT);
    pinMode(23, OUTPUT);
    pinMode(24, OUTPUT);
    pinMode(25, OUTPUT);
    pinMode(27, OUTPUT);
    pinMode(28, OUTPUT);
    pinMode(29, OUTPUT);
}

void control_forward() {
    printf("forward\n");
    digitalWrite (21, 1) ;  // On
    digitalWrite (22, 1) ;
    digitalWrite (25, 1) ;
    digitalWrite (27, 1) ;
    delay (DELAY_TIME);
    digitalWrite (21, 0) ;  // Off
    digitalWrite (22, 0) ;
    digitalWrite (25, 0) ;
    digitalWrite (27, 0) ;
}

void control_back() {
    printf("back\n");
    digitalWrite (23, 1) ;  // On
    digitalWrite (24, 1) ;
    digitalWrite (28, 1) ;
    digitalWrite (29, 1) ;
    delay (DELAY_TIME);
    digitalWrite (23, 0) ;  // Off
    digitalWrite (24, 0) ;
    digitalWrite (28, 0) ;
    digitalWrite (29, 0) ;
}

void control_rotate_left() {
    printf("rotate left\n");
    digitalWrite (22, 1) ;  // On
    delay (DELAY_TIME);
    digitalWrite (22, 0) ;  // Off
}

void control_rotate_right() {
    printf("rotate right\n");
    digitalWrite (21, 1) ;  // On
    delay (DELAY_TIME);
    digitalWrite (21, 0) ;  // Off
}

void control_left_forward() {

}

void control_right_forward() {

}



