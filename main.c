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

void fail_exit(const char *message) {
    char buf[BUFSIZ];
    snprintf(buf, BUFSIZ, "\nError:\n%s.\n\nError code: %i\nMessage from system", message, errno);
    perror(buf);
    exit(EXIT_FAILURE);
}

int main() {
    char read_buf[BUFSIZ];
    struct sockaddr_in client_inf;
    //socket descriptor
    int sock_d = socket(AF_INET, SOCK_DGRAM, 0);
        if (sock_d == -1) fail_exit("Socket didn't create");
    struct sockaddr_in addr_inf = {
            .sin_family = AF_INET,
            .sin_port = htons(SRV_PORT),
            .sin_addr.s_addr = htonl(INADDR_ANY)
    };
    int b_res = bind(sock_d, (const struct sockaddr *) &addr_inf, sizeof(addr_inf));
        if (b_res == -1) fail_exit("Failed bind socket for server port");

    puts("Robot search server ready!");
    #pragma clang diagnostic push
    #pragma clang diagnostic ignored "-Wmissing-noreturn"
        while(true) {
            socklen_t socklen = sizeof(client_inf);
            ssize_t bytes_read = recvfrom(sock_d, read_buf, BUFSIZ, 0, (struct sockaddr *) &client_inf, &socklen);
            read_buf[bytes_read] = '\0';
            puts("An packet catch.");
            //check received packet and response
            if (!strcmp(read_buf, CLIENT_MSG)) {
                sleep(3);
                client_inf.sin_port = CLIENT_PORT;
                int send_sock_d = socket(AF_INET, SOCK_DGRAM, 0);
                    if (send_sock_d == -1) puts("Sender socket didn't create.");
                sendto(send_sock_d, SERVER_MSG, sizeof(SERVER_MSG), 0, (const struct sockaddr *) &client_inf,
                        sizeof(client_inf));
                close(send_sock_d);
                char str[INET_ADDRSTRLEN];
                inet_ntop(AF_INET, &(client_inf.sin_addr), str, INET_ADDRSTRLEN);
                printf("Response was send to %s.\n", str);
            }
        }
    #pragma clang diagnostic pop
}