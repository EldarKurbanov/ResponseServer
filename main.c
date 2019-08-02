#pragma clang diagnostic ignored "-Wmissing-noreturn"

#include <stdio.h>
#include <sys/socket.h>
#include <errno.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <string.h>
#include <zconf.h>
#include <arpa/inet.h>

#define SRV_PORT 1031
#define CLIENT_PORT 1032
#define CLIENT_MSG "Robot, where are you?"

const char SERVER_MSG[] = "I'm here!";

void err_exit(const char *message) {
    char buf[BUFSIZ];
    snprintf(buf, BUFSIZ, "\nError %i: %s", errno, message);
    perror(buf);
    exit(EXIT_FAILURE);
}

int main() {

    socklen_t socklen = sizeof(struct sockaddr_in);
    char read_buf[BUFSIZ];

    struct sockaddr_in client_inf;

    struct sockaddr_in addr_inf = {
            .sin_family = AF_INET,
            .sin_port = htons(SRV_PORT),
            .sin_addr.s_addr = htonl(INADDR_ANY)
    };

    // create socket
    int sock_d = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock_d == -1)
        err_exit("Couldn't create socket.");

    // bind
    int b_res = bind(sock_d, (const struct sockaddr *) &addr_inf, sizeof(addr_inf));
    if (b_res == -1)
        err_exit("Bind failed.");

    puts("Robot search server initialized!");

    // listen
    while(true)
    {
        ssize_t bytes_read = recvfrom(sock_d, read_buf, BUFSIZ, 0, (struct sockaddr *) &client_inf, &socklen);
        read_buf[bytes_read] = '\0';
        printf("Received message: '%s' ", read_buf);

        //check received packet and response
        if (!strcmp(read_buf, CLIENT_MSG))
        {
            usleep(100);
            client_inf.sin_port = htons(CLIENT_PORT);

            int send_sock_d = socket(AF_INET, SOCK_DGRAM, 0);
            if (send_sock_d == -1) {
                puts("Couldn't create send socket.");
            }

            sendto(send_sock_d, SERVER_MSG, sizeof(SERVER_MSG), 0, (struct sockaddr *) &client_inf, sizeof(client_inf));
            close(send_sock_d);

            // print client addr
            char str[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, &(client_inf.sin_addr), str, INET_ADDRSTRLEN);
            printf("Response send to %s.\n", str);

        }
    }

}