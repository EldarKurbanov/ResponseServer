//
// Created by mrkotyk on 07.08.2019.
//

#ifndef RESPONSESERVER_PARSE_REQ_RES_H
#define RESPONSESERVER_PARSE_REQ_RES_H

#define CONNECTION_REQUEST_METHOD "connectToRobot"
#define RESPONSE_SUCCESS_STR "{\"jsonrpc\":\"2.0\",\"result\":\"allowed\",\"id\":1}"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../lib/cJSON.h"

struct jsonrpc_request{
    char *jsonrpc;
    char *method;
    char **params;
    int id;
};

struct jsonrpc_response{
    char *jsonrpc;
    char *result;
    char *error;
    int id;
};

int is_connection_request(char* request);

struct jsonrpc_request *parse_request(char *request);

char* response_to_json_str(struct jsonrpc_response *response);

#endif //RESPONSESERVER_PARSE_REQ_RES_H
