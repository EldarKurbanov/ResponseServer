//
// Created by mrkotyk on 06.08.2019.
//

#ifndef RESPONSESERVER_ERR_EXIT_H
#define RESPONSESERVER_ERR_EXIT_H

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

void err_exit(const char *message) {
    char buf[BUFSIZ];
    snprintf(buf, BUFSIZ, "\nError [%i] %s", errno, message);
    perror(buf);
    exit(EXIT_FAILURE);
}

#endif //RESPONSESERVER_ERR_EXIT_H
