//
// Created by mrkotyk on 04.08.2019.
//

#include "control_process.h"

void process_button_input(struct control_button *input)
{   // TODO call gpio methods
    switch (input->state) {
        case CONTROL_STATE_FORWARD:
            printf("forward");
            break;
        case CONTROL_STATE_BACK:
            printf("back");
            break;
        case CONTROL_STATE_ROTATE_LEFT:
            printf("rotate left");
            break;
        case CONTROL_STATE_ROTATE_RIGHT:
            printf("rotate right");
            break;
        case CONTROL_STATE_LEFT_FORWARD:
            printf("left forward");
            break;
        case CONTROL_STATE_RIGHT_FORWARD:
            printf("right forward");
            break;
        default:
            printf("<process_button_input> wrong control state");
    }
}

void process_joystick_input(struct control_joystick *input)
{   // TODO call gpio methods
    printf("x=%f y=%f", input->x, input->y);
}

void process_path_input(struct control_path *input)
{   // TODO call gpio methods
    printf("path t=%lo", input->t);
}

void process_control(char *message)
{
    cJSON *control_json = cJSON_Parse(message);

    switch (get_control_type(control_json)) {
        case CONTROL_TYPE_BUTTON: {
            struct control_button *input = parse_control_button(control_json);
            process_button_input(input);
            break;
        }
        case CONTROL_TYPE_JOYSTICK: {
            struct control_joystick *input = parse_control_joystick(control_json);
            process_joystick_input(input);
            break;
        }
        case CONTROL_TYPE_PATH: {
            struct control_path *input = parse_control_path(control_json);
            process_path_input(input);
            break;
        }
        default:
            printf("<control_loop>: Wrong control "
                   "type in client message.");
    }
}
