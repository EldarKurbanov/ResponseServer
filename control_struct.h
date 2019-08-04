//
// Created by mrkotyk on 04.08.2019.
//

#ifndef RESPONSESERVER_CONTROL_STRUCT_H
#define RESPONSESERVER_CONTROL_STRUCT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib/cJSON.h"

#define CONTROL_TYPE_ERR (-1)
#define CONTROL_TYPE_BUTTON 1
#define CONTROL_TYPE_JOYSTICK 2
#define CONTROL_TYPE_PATH 3

#define CONTROL_STATE_FORWARD 1
#define CONTROL_STATE_BACK 2
#define CONTROL_STATE_ROTATE_LEFT 3
#define CONTROL_STATE_ROTATE_RIGHT 4
#define CONTROL_STATE_LEFT_FORWARD 5
#define CONTROL_STATE_RIGHT_FORWARD 6

struct control_button{
    const int state;
    const long t;
};

struct control_joystick{
    const double x;
    const double y;
    const long t;
};

struct control_path{
    const char* unit;
    const double** points;
    const long t;
};

int get_control_type(cJSON *control_json);

struct control_button* parse_control_button(cJSON *control_json);

struct control_joystick* parse_control_joystick(cJSON *control_json);

struct control_path* parse_control_path(cJSON *control_json);

#endif //RESPONSESERVER_CONTROL_STRUCT_H
