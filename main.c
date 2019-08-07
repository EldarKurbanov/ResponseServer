#pragma clang diagnostic ignored "-Wmissing-noreturn"

#include "control/process_control.h"
#include "broadcast/broadcast.h"
#include "json/parse_req_res.h"

int broadcast_connect()
{
    int sock_d = broadcast_init(1031, 1032);

    while(true) {
        usleep(100);
        char *client_message = broadcast_recv(sock_d);
        //check received packet and response
        if (!is_connection_request(client_message)) {
            broadcast_send(RESPONSE_SUCCESS_STR);
            break;
        }
    }

    return sock_d;
}

int main()
{
    int sock_d = broadcast_connect();
    while(true) {
        char* message = broadcast_recv(sock_d);

        if(!is_connection_request(message)) {
            broadcast_send(RESPONSE_SUCCESS_STR);
            continue;
        }

        process_control(message);
    }
}

