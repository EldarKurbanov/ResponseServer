//
// Created by mrkotyk on 04.08.2019.
//
#include "control_struct.h"

int get_control_type(cJSON *control_json)
{
    int type = 0;

    if (control_json == NULL)
    {
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL)
            fprintf(stderr, "<get_control_type> parse error before: %s\n", error_ptr);

        type = CONTROL_TYPE_ERR;
        goto end;
    }

    const cJSON *type_obj = cJSON_GetObjectItemCaseSensitive(control_json, "type");
    if (cJSON_IsString(type_obj) && (type_obj->valuestring != NULL))
    {
        char *type_str = type_obj->valuestring;
        if(!strcmp(type_str, "button")) {
            type = CONTROL_TYPE_BUTTON;
        } else if(!strcmp(type_str, "joystick")) {
            type = CONTROL_TYPE_JOYSTICK;
        } else if(!strcmp(type_str, "path")) {
            type = CONTROL_TYPE_PATH;
        } else {
            type = CONTROL_TYPE_ERR;
        }
    }

end:
    cJSON_Delete(control_json);
    return type;
}

struct control_button* parse_control_button(cJSON *control_json)
{
    cJSON *move_state = cJSON_GetObjectItemCaseSensitive(control_json, "move_state");
    cJSON *t = cJSON_GetObjectItemCaseSensitive(control_json, "t");
    char *endptr = NULL;

    if(!cJSON_IsNumber(move_state) || !cJSON_IsNumber(t)) {
        fprintf(stderr,"<parse_control_button> parse error, wrong parameter type.\n");
        return NULL;
    }

    struct control_button* control_struct = &(struct control_button) {
            .state = move_state->valueint,
            // convert string to long
            .t = strtol(t->string, &endptr, 10)
    };

    return control_struct;
}

struct control_joystick* parse_control_joystick(cJSON *control_json)
{
    cJSON *x = cJSON_GetObjectItemCaseSensitive(control_json, "x");
    cJSON *y = cJSON_GetObjectItemCaseSensitive(control_json, "y");
    cJSON *t = cJSON_GetObjectItemCaseSensitive(control_json, "t");
    char *endptr = NULL;

    if(!cJSON_IsNumber(x) || !cJSON_IsNumber(y) || !cJSON_IsNumber(t)) {
        fprintf(stderr,"<parse_control_joystick> parse error, wrong parameter type.\n");
        return NULL;
    }

    struct control_joystick* control_struct = &(struct control_joystick) {
            .x = x->valuedouble,
            .y = y->valuedouble,
            .t = strtol(t->string, &endptr, 10)
    };

    return control_struct;
}

struct control_path* parse_control_path(cJSON *control_json)
{
    cJSON *points = cJSON_GetObjectItemCaseSensitive(control_json, "points");
    cJSON *count = cJSON_GetObjectItemCaseSensitive(control_json, "count");
    cJSON *unit = cJSON_GetObjectItemCaseSensitive(control_json, "unit");
    cJSON *t = cJSON_GetObjectItemCaseSensitive(control_json, "t");
    char *endptr = NULL;
    cJSON *point;


    if(!cJSON_IsString(unit) || !cJSON_IsArray(points) || !cJSON_IsNumber(t)) {
        fprintf(stderr,"<parse_control_joystick> parse error, wrong parameter type.\n");
        return NULL;
    }

    double** points_arr = malloc(count->valueint * sizeof(int*));
    int i = 0;

    cJSON_ArrayForEach(point, points)
    {
        cJSON *x = cJSON_GetObjectItemCaseSensitive(point, "x");
        cJSON *y = cJSON_GetObjectItemCaseSensitive(point, "y");

        points_arr[i] = malloc(2 * sizeof(int));
        points_arr[i][0] = x->valuedouble;
        points_arr[i][1] = y->valuedouble;

        i++;
    }

    struct control_path* control_struct = &(struct control_path) {
            .unit = unit->valuestring,
            .points = (const double **) points_arr,
            .t = strtol(t->string, &endptr, 10)
    };

    return control_struct;
}