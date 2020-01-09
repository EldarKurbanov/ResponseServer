#include <stdbool.h>
#include <arpa/inet.h>
#include "tcp.h"

char addr_buf[INET_ADDRSTRLEN];
char read_buf[BUFSIZ];
socklen_t socklen;
#define PORT 1032
struct sockaddr_in client_inf;

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

int tcp_init_connect(int srv_port) {
    int sockfd, connfd;
    struct sockaddr_in servaddr, cli;

    // socket create and varification
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("socket creation failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully created..\n");
    bzero(&servaddr, sizeof(servaddr));

    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("192.168.100.7");
    servaddr.sin_port = htons(1035);
    return sockfd;
}

int tcp_accept(int sock_d) {
    // Accept the data packet from client and verification
    //struct sockaddr_in client_inf;
    socklen_t client_len = sizeof(client_inf);
    int conn_d = accept(sock_d, (struct sockaddr *) &client_inf, &client_len);
    if (conn_d < 0)
        err_exit("tcp accept failed");

    // printf("Connection accepted.\n");
    return conn_d;
}

char* tcp_read(int conn_d) {
    read:
    bzero(read_buf, BUFSIZ);
    read(conn_d, read_buf, BUFSIZ);
    if (strcmp(read_buf, "") == 0) {
        goto read;
    }
    printf("Received message: '%s'\n", read_buf);
    return read_buf;
}

struct tcp_info_accept tcp_accept_read(int sock_d) {
    // Accept the data packet from client and verification
    //struct sockaddr_in client_inf;
    socklen_t client_len = sizeof(client_inf);
    int conn_d = accept(sock_d, (struct sockaddr *) &client_inf, &client_len);
    if (conn_d < 0)
        err_exit("tcp accept failed");

    // printf("Connection accepted.\n");
    bzero(read_buf, BUFSIZ);
    read(conn_d, read_buf, BUFSIZ);
    printf("Received message: '%s'\n", read_buf);
    struct tcp_info_accept info;
    info.client_inf = client_inf;
    info.message = read_buf;
    info.conn_d = conn_d;
    return info;
}

void tcp_conn_send(int sock_d, struct sockaddr_in client_inf2, const char* message) {
    // connect the client socket to server socket
    //struct sockaddr_in client_inf;

    /*bzero(&client_inf, sizeof(client_inf));
    client_inf.sin_family = AF_INET;
    client_inf.sin_addr.s_addr = inet_addr("192.168.100.7");
    client_inf.sin_port = htons(1036);*/
    if (connect(sock_d, (struct sockaddr*) &client_inf, sizeof(client_inf)) != 0) {
        printf("connection with the server failed...\n");
        err_exit("failed");
        exit(0);
    }
    else
        printf("connected to the server..\n");

    write(sock_d, message, sizeof(message));

}

void tcp_send(int conn_d, const char* message) {
    write(conn_d, message, strlen(message));
}

void tcp_stop_self() {
    int sockfd, connfd;
    struct sockaddr_in servaddr, cli;

    // socket create and varification
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("socket creation failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully created..\n");
    bzero(&servaddr, sizeof(servaddr));

    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(1033);

    // connect the client socket to server socket
    if (connect(sockfd, (struct sockaddr*) &servaddr, sizeof(servaddr)) != 0) {
        printf("connection with the server failed...\n");
        exit(0);
    }
    const char* stop_message = "STOP";
    write(sockfd, stop_message, sizeof(stop_message));
    close(sockfd);
}
