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

/* print message and exit with error */
void err_exit(const char* message);

/* creates socket and return */
int broadcast_init(int SRV_PORT, int CLIENT_PORT);

/* send message to broadcast addr with port CLIENT_PORT */
void broadcast_send(int broadcast_sock_d, const char* CLIENT_MSG, const char* SERVER_MSG);

void broadcast_close();

#endif //RESPONSESERVER_BROADCAST_H
