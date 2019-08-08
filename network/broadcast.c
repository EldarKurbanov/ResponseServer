#include "broadcast.h"

struct sockaddr_in client_inf;
int internal_client_port;

char addr_buf[INET_ADDRSTRLEN];
char read_buf[BUFSIZ];

socklen_t socklen;

int broadcast_init(const int srv_port, const int client_port)
{
    socklen = sizeof(struct sockaddr_in);

    struct sockaddr_in addr_inf = {
            .sin_family = AF_INET,
            .sin_port = htons(srv_port),
            .sin_addr.s_addr = htonl(INADDR_ANY),
    };

    internal_client_port = client_port;

    // create
    int sock_d = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock_d == -1)
        err_exit("Couldn't create socket.");

    // bind
    int b_res = bind(sock_d, (const struct sockaddr *) &addr_inf, sizeof(addr_inf));
    if (b_res == -1)
        err_exit("bind failed");

    printf("Robot search server initialized!\n");

    return sock_d;
}

void broadcast_send(const char *message)
{
    client_inf.sin_port = htons(internal_client_port);

    int send_sock_d = socket(AF_INET, SOCK_DGRAM, 0);
    if (send_sock_d == -1) {
        puts("Couldn't create send socket.");
    }

    sendto(send_sock_d, message, strlen(message), 0, (struct sockaddr *) &client_inf, sizeof(client_inf));
    close(send_sock_d);

    printf("Broadcast response '%s' send to %s\n", message, broadcast_client_addr());
}

char* broadcast_recv(int broadcast_sock_d)
{
    ssize_t bytes_read = recvfrom(broadcast_sock_d, read_buf, BUFSIZ, 0, (struct sockaddr *) &client_inf, &socklen);
    read_buf[bytes_read] = '\0';
    printf("Broadcast received message: '%s'\n", read_buf);
    return read_buf;
}

struct sockaddr_in* broadcast_get_client() { return &client_inf; }

char* broadcast_client_addr() {
    inet_ntop(AF_INET, &(client_inf.sin_addr), addr_buf, INET_ADDRSTRLEN);
    return addr_buf;
}

