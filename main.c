#pragma clang diagnostic ignored "-Wmissing-noreturn"

#include "control/process_control.h"
#include "network/broadcast.h"
#include "json/parse_req_res.h"
#include "network/tcp.h"

#define SRV_PORT 1031
#define CLNT_PORT 1032

void broadcast_connect()
{
    int sock_d = broadcast_init(SRV_PORT, CLNT_PORT);

    while(true) {
        usleep(10000);
        char *client_message = broadcast_recv(sock_d);
        //check received packet and response
        if (check_request_method(client_message, PERMISSION_REQUEST_METHOD)) {
            broadcast_send(RESPONSE_ALLOWED_STR);
        } else if (check_request_method(client_message, CONNECT_METHOD)) {
            broadcast_send(RESPONSE_CONNECT_SUCCESS);
            printf("Successfully connected!\n");
            close(sock_d);
            return;
        }
    }
}

int main()
{
    broadcast_connect();
    int sock_d = tcp_init(SRV_PORT);
    control_init();

    while(true)
    {
        int conn_d = tcp_accept(sock_d);
        char *message = tcp_read(conn_d);
        process_control(message);
    }
}

