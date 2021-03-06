//
// Created by mrkotyk on 01.08.2019.
//

#ifndef RESPONSESERVER_BROADCAST_H
#define RESPONSESERVER_BROADCAST_H

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <stdbool.h>
#include <string.h>
#include <zconf.h>
#include <arpa/inet.h>
#include "../err_exit.h"

/* creates socket and return */
int broadcast_init(int srv_port, int client_port);

/* send message to broadcast addr with port CLIENT_PORT */
void broadcast_send(const char *message);

/* return client message */
char* broadcast_recv(int broadcast_sock_d);

/* return string with last client addr */
char* broadcast_client_addr();

/* returns last connected client information */
struct sockaddr_in* broadcast_get_client();

void tcp_close(int sock_d);

#endif //RESPONSESERVER_BROADCAST_H
