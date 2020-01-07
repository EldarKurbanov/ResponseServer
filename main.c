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
            broadcast_send(RESPONSE_CONNECT_READY);
            client_message = broadcast_recv(sock_d);
            if (check_request_method(client_message, REQUEST_SESSION_KEY)) {
                broadcast_send(session_key_to_json(generate_session_key()));
                client_message = broadcast_recv(sock_d);
                if (!check_request_method(client_message, KEY_ACCEPTED)) {
                    puts("Client doesn't accept the session key.");
                    close(sock_d);
                    return false;
                }
            } else {
                puts("Client doesn't request session key.");
                close(sock_d);
                return false;
            }
            broadcast_send(RESPONSE_CONNECT_SUCCESS);
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
        if (!broadcast_connect()) continue;

        int sock_d = tcp_init(SRV_PORT);
        control_init();
        startKeepAlive();

        int conn_d = tcp_accept(sock_d);
        char *message = tcp_read(conn_d);
        process_control(message);

        close(conn_d);
        close(sock_d);
    }
}

