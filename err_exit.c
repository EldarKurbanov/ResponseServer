#include "err_exit.h"

void err_exit(const char *message) {
    char buf[BUFSIZ];
    snprintf(buf, BUFSIZ, "\nError [%i] %s", errno, message);
    perror(buf);
    exit(EXIT_FAILURE);
}
