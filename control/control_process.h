//
// Created by mrkotyk on 04.08.2019.
//

#ifndef RESPONSESERVER_CONTROL_PROCESS_H
#define RESPONSESERVER_CONTROL_PROCESS_H

#include "control_struct.h"

void process_control(char *message);

void process_button_input(struct control_button *input);

void process_joystick_input(struct control_joystick *input);

void process_path_input(struct control_path *input);

#endif //RESPONSESERVER_CONTROL_PROCESS_H
