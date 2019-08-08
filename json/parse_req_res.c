//
// Created by mrkotyk on 07.08.2019.
//

#include "parse_req_res.h"

int check_request_method(const char *request, const char *method_name)
{
    cJSON *request_json = cJSON_Parse(request);
    cJSON *method = cJSON_GetObjectItemCaseSensitive(request_json, "method");

    return request_json != NULL &&
           method != NULL &&
           cJSON_IsString(method) &&
           strcmp(method->valuestring, method_name) == 0;
}

// TODO add params parse
struct jsonrpc_request *parse_request(const char *request)
{
    cJSON *request_json = cJSON_Parse(request);
    cJSON *method = cJSON_GetObjectItemCaseSensitive(request_json, "method");
    cJSON *params = cJSON_GetObjectItemCaseSensitive(request_json, "params");
    cJSON *id = cJSON_GetObjectItemCaseSensitive(request_json, "id");

    struct jsonrpc_request *result = &(struct jsonrpc_request){
        .jsonrpc = "2.0",
        .method = method->valuestring,
        // .params = "",
        .id = id->valueint,
    };

    return result;
}

// TODO all
char* response_str(struct jsonrpc_response *response)
{
    cJSON *response_json = cJSON_CreateObject();
    cJSON *result_json = cJSON_CreateObject();

    cJSON_AddStringToObject(response_json, "result", "Awesome 4K");
}
