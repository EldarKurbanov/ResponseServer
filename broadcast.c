#include "broadcast.h"

socklen_t socklen = sizeof(struct sockaddr_in);
struct sockaddr_in client_inf;
char read_buf[BUFSIZ];
int client_port;

void err_exit(const char* message) {
    char buf[BUFSIZ];
    snprintf(buf, BUFSIZ, "\nError %i: %s", errno, message);
    perror(buf);
    exit(EXIT_FAILURE);
}

int broadcast_init(const int SRV_PORT, const int CLIENT_PORT) {

    struct sockaddr_in addr_inf = {
            .sin_family = AF_INET,
            .sin_port = htons(SRV_PORT),
            .sin_addr.s_addr = htonl(INADDR_ANY)
    };

    client_port = CLIENT_PORT;

    // create socket
    int sock_d = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock_d == -1)
        err_exit("Couldn't create socket.");

    // bind
    int b_res = bind(sock_d, (const struct sockaddr *) &addr_inf, sizeof(addr_inf));
    if (b_res == -1)
        err_exit("Bind failed.");

    puts("Robot search server initialized!");

    return sock_d;

}

void broadcast_send(int broadcast_sock_d, const char* CLIENT_MSG, const char* SERVER_MSG)
{
    ssize_t bytes_read = recvfrom(broadcast_sock_d, read_buf, BUFSIZ, 0, (struct sockaddr *) &client_inf, &socklen);
    read_buf[bytes_read] = '\0';
    printf("Received message: '%s' ", read_buf);

    //check received packet and response
    if (!strcmp(read_buf, CLIENT_MSG))
    {
        usleep(100);
        client_inf.sin_port = htons(client_port);

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
