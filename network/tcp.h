//
// Created by mrkotyk on 08.08.2019.
//

#ifndef RESPONSESERVER_TCP_H
#define RESPONSESERVER_TCP_H

#define MAX_CLIENTS_LISTENING 5

#include "../err_exit.h"
#include <netinet/in.h>
#include <zconf.h>
#include <strings.h>
#include <string.h>

struct tcp_info_accept {
    struct sockaddr_in client_inf;
    char* message;
    int conn_d;
};

/* creates socket and start listen */
int tcp_init(int srv_port);
int tcp_init_connect(int srv_port);

/* get message from client */
int tcp_accept(int sock_d);

char* tcp_read(int conn_d);

void tcp_stop_self();

void tcp_conn_send(int sock_d, struct sockaddr_in client_inf, const char* message);
struct tcp_info_accept tcp_accept_read(int sock_d);

void tcp_send(int conn_d, const char* message);

#endif //RESPONSESERVER_TCP_H
