//
// Created by mrkotyk on 07.08.2019.
//

#ifndef RESPONSESERVER_PARSE_REQ_RES_H
#define RESPONSESERVER_PARSE_REQ_RES_H

#define PERMISSION_REQUEST_METHOD "connectionRequest"
#define CONNECT_METHOD "connectToRobot"

#define RESPONSE_ALLOWED_STR "{\"jsonrpc\":\"2.0\",\"result\":\"allowed\",\"id\":1}"
#define RESPONSE_CONNECT_SUCCESS "{\"jsonrpc\":\"2.0\",\"result\":\"success\",\"id\":1}"

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

int check_request_method(const char* request, const char* method_name);

struct jsonrpc_request *parse_request(const char *request);

char* response_to_json_str(const struct jsonrpc_response *response);

#endif //RESPONSESERVER_PARSE_REQ_RES_H
