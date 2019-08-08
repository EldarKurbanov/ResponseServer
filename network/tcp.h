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

/* creates socket and start listen */
int tcp_init(int srv_port);

/* get message from client */
int tcp_accept(int sock_d);

char* tcp_read(int conn_d);

#endif //RESPONSESERVER_TCP_H
