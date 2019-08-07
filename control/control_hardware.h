//
// Created by mrkotyk on 05.08.2019.
//

#ifndef RESPONSESERVER_CONTROL_HARDWARE_H
#define RESPONSESERVER_CONTROL_HARDWARE_H

#include <wiringPi.h>

void control_hardware_setup();

void control_hardware_setup_pins();

void control_hardware_forward(unsigned int how_long);

#endif //RESPONSESERVER_CONTROL_HARDWARE_H
