//
// Created by mrkotyk on 04.08.2019.
//

#ifndef RESPONSESERVER_PROCESS_CONTROL_H
#define RESPONSESERVER_PROCESS_CONTROL_H

#if defined(__arm__)
    #include "control_hardware.h"
#else
    #include "control_emulate.h"
#endif

#include "../json/control_struct.h"

void process_control(const char *message);

void process_button_input(const struct control_button *input);

void process_joystick_input(const struct control_joystick *input);

void process_path_input(const struct control_path *input);

#endif //RESPONSESERVER_PROCESS_CONTROL_H
