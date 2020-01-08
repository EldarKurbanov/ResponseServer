#pragma clang diagnostic ignored "-Wmissing-noreturn"

#include "control/process_control.h"
#include "network/broadcast.h"
#include "json/parse_req_res.h"
#include "network/tcp.h"
#include "network/keepalive.h"
#include "security/session.h"
#include <stdbool.h>

#define SRV_PORT 1031
#define CLNT_PORT 1032
#define SRV_TCP_PORT 1033

int conn_d;
int sock_d_tcp;

bool broadcast_connect()
{
    int sock_d = broadcast_init(SRV_PORT, CLNT_PORT);

    while(true) {
        usleep(10000);
        char *client_message = broadcast_recv(sock_d);
        //check received packet and response
        if (check_request_method(client_message, PERMISSION_REQUEST_METHOD)) {
            broadcast_send(RESPONSE_ALLOWED_STR);
        } else if (check_request_method(client_message, CONNECT_METHOD)) {
            //tcp
            //startKeepAlive();
            sock_d_tcp = tcp_init(SRV_TCP_PORT);
            client_message = tcp_accept_read(sock_d_tcp);
            if (strcmp(client_message, REQUEST_SESSION_KEY) != 0) {
                puts("Client doesn't request session key");
                close(sock_d_tcp);
                close(sock_d);
                return false;
            }
            sock_d_tcp = tcp_init(SRV_TCP_PORT);
            tcp_conn_send(sock_d_tcp, session_key_to_json(generate_session_key()));
            sock_d_tcp = tcp_init(SRV_TCP_PORT);
            client_message = tcp_accept_read(sock_d_tcp);
            if (strcmp(client_message, KEY_ACCEPTED) != 0) {
                puts("Client doesn't accept session key");
                close(sock_d_tcp);
                close(sock_d);
                return false;
            }
            sock_d_tcp = tcp_init(SRV_TCP_PORT);
            tcp_conn_send(sock_d_tcp, RESPONSE_CONNECT_SUCCESS);

            printf("Successfully connected!\n");
            close(sock_d);
            return true;
        }
    }
}

int main()
{
    while (true) {
        security_init();
        if (!broadcast_connect()) {
            close(conn_d);
            close(sock_d_tcp);
            continue;
        }

        control_init();

        //conn_d = tcp_accept(sock_d);
        while (true) {
            conn_d = tcp_accept(sock_d_tcp);
            char *message = tcp_read(conn_d);
            process_control(message);
        }
    }
}

