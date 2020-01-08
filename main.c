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
#define SRV_TCP_A_PORT 1034
#define SRV_TCP_C_PORT 1035

int sock_tcp_a;
int sock_tcp_c;
int sock_udp;

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
            struct tcp_info_accept info = tcp_accept_read(sock_tcp_a);
            client_message = info.message;
            if (strcmp(client_message, REQUEST_SESSION_KEY) != 0) {
                puts("Client doesn't request session key");
                close(sock_d);
                return false;
            }
            sleep(1);
            tcp_conn_send(sock_tcp_c, info.client_inf, session_key_to_json(generate_session_key()));
            client_message = tcp_accept_read(sock_tcp_a).message;
            if (strcmp(client_message, KEY_ACCEPTED) != 0) {
                puts("Client doesn't accept session key");
                close(sock_d);
                return false;
            }
            tcp_conn_send(sock_tcp_c, info.client_inf,RESPONSE_CONNECT_SUCCESS);

            printf("Successfully connected!\n");
            close(sock_d);
            return true;
        }
    }
}

int main()
{
    sock_tcp_a = tcp_init(SRV_TCP_A_PORT);
    sock_tcp_c = tcp_init_connect(SRV_TCP_C_PORT);
    while (true) {
        security_init();
        if (!broadcast_connect()) {
            close(sock_tcp_a);
            close(sock_tcp_c);
            continue;
        }

        control_init();

        //conn_d = tcp_accept(sock_d);
        while (true) {
            tcp_accept(sock_tcp_a);
            char *message = tcp_read(sock_tcp_a);
            process_control(message);
        }
    }
}

