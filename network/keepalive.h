//
// Created by eldar on 04.01.2020.
//

#ifndef RESPONSESERVER_KEEPALIVE_H
#define RESPONSESERVER_KEEPALIVE_H

#include <pthread.h>
#include <stdbool.h>
#include "../err_exit.h"
#include <time.h>
#include <bits/sigthread.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include "tcp.h"

#define KEEPALIVE_TIME 5 //sec
#define KEEPALIVE_PORT 1033
#define KEEPALIVE_BUFFER_SIZE 1024
#define KEEPALIVE_REQUEST "Client alive!"
#define KEEPALIVE_RESPONSE "Robot too!"

void *keep_alive_receive_thread(void *data);
void *keep_alive_thread(void *data);
void startKeepAlive();
void stopKeepAlive();
bool isClientAlive();

#endif //RESPONSESERVER_KEEPALIVE_H
