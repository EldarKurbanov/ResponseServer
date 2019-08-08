#include "tcp.h"

struct sockaddr_in client_inf;
char addr_buf[INET_ADDRSTRLEN];
char read_buf[BUFSIZ];
socklen_t socklen;

int tcp_init(int srv_port)
{
    socklen = sizeof(struct sockaddr_in);

    struct sockaddr_in addr_inf = {
            .sin_family = AF_INET,
            .sin_port = htons(srv_port),
            .sin_addr.s_addr = htonl(INADDR_ANY),
    };

    // create
    int sock_d = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_d < 0)
        err_exit("Couldn't create socket.");

    // bind
    int b_res = bind(sock_d, (const struct sockaddr *) &addr_inf, sizeof(addr_inf));
    if (b_res < 0)
        err_exit("bind failed");

    printf("Robot tcp server initialized!\n");

    // listen
    if (listen(sock_d, MAX_CLIENTS_LISTENING) < 0)
        err_exit("tcp listen failed");

    return sock_d;
}

int tcp_accept(int sock_d) {
    // Accept the data packet from client and verification
    socklen_t client_len = sizeof(client_inf);
    int conn_d = accept(sock_d, (struct sockaddr *) &client_inf, &client_len);
    if (conn_d < 0)
        err_exit("tcp accept failed");

    // printf("Connection accepted.\n");

    return conn_d;
}

char* tcp_read(int conn_d) {
    bzero(read_buf, BUFSIZ);
    read(conn_d, read_buf, BUFSIZ);
    printf("Received message: '%s'\n", read_buf);
    return read_buf;
}

