//
// Created by mrkotyk on 04.08.2019.
//

#include "process_control.h"

void process_button_input(const struct control_button *input)
{
    switch (input->state) {
        case CONTROL_STATE_FORWARD:       control_forward();
            break;
        case CONTROL_STATE_BACK:          control_back();
            break;
        case CONTROL_STATE_ROTATE_LEFT:   control_rotate_left();
            break;
        case CONTROL_STATE_ROTATE_RIGHT:  control_rotate_right();
            break;
        case CONTROL_STATE_LEFT_FORWARD:  control_left_forward();
            break;
        case CONTROL_STATE_RIGHT_FORWARD: control_right_forward();
            break;
        default:
            fprintf(stderr,"<process_button_input> wrong control state.\n");
    }
}

void process_joystick_input(const struct control_joystick *input)
{   // TODO call gpio methods
    printf("x=%f y=%f\n", input->x, input->y);
}

void process_path_input(const struct control_path *input)
{   // TODO call gpio methods
    printf("path t=%lo\n", input->t);
}

void process_control(const char *message)
{
    if(strlen(message) == 0)
        return;

    cJSON *control_json = cJSON_Parse(message);
    if (control_json == NULL) {
        print_json_err();
        return;
    }

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
            fprintf(stderr,"<process_control>: Wrong control "
                                  "type in client message.\n");
    }

    cJSON_Delete(control_json);
}
