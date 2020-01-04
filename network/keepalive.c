//
// Created by eldar on 04.01.2020.
//

#include "keepalive.h"

time_t lastKeepAliveReceivedTime = 0;
bool clientAlive = false;
pthread_t *thread_pointer;
int socket_descriptor;

void *keep_alive_receive_thread(void *data) {
    char buffer[KEEPALIVE_BUFFER_SIZE];
    struct sockaddr_in server_addr, client_addr;

    // Creating socket file descriptor
    if ((socket_descriptor = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        err_exit("Socket for keep alive doesn't created");
    }

    memset(&server_addr, 0, sizeof(server_addr));
    memset(&client_addr, 0, sizeof(client_addr));

    // Filling server information
    server_addr.sin_family    = AF_INET; // IPv4
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(KEEPALIVE_PORT);

    // Bind the socket with the server address
    if (bind(socket_descriptor, (const struct sockaddr *)&server_addr, sizeof(server_addr)) < 0 ) {
        err_exit("Port for keep alive doesn't bind");
    }

    unsigned int len = sizeof(client_addr);  //len is value/resuslt

    while (clientAlive) {
        unsigned int n = recvfrom(socket_descriptor, (char *)buffer, KEEPALIVE_BUFFER_SIZE,MSG_WAITALL,
                                  (struct sockaddr *) &client_addr, &len);
        buffer[n] = '\0';

        if (strcmp(buffer, KEEPALIVE_REQUEST) != 0) {
            if (strcmp(buffer, "STOP") != 0) {
                puts("Unknown packet received on keep alive port!");
                continue;
            } else {
                //STOP
                break;
            }
        }
        sendto(socket_descriptor, KEEPALIVE_RESPONSE, strlen(KEEPALIVE_RESPONSE),
               MSG_CONFIRM, (const struct sockaddr *) &client_addr, len);
        lastKeepAliveReceivedTime = time(NULL);
    }
    pthread_exit(NULL);
}

//timer thread
void *keep_alive_thread(void *data) {
    lastKeepAliveReceivedTime = time(NULL);
    pthread_t receiveThread;
    pthread_create(&receiveThread, NULL, keep_alive_receive_thread, NULL);
    while (clientAlive) {
        time_t current_time = time(NULL);
        if (current_time - lastKeepAliveReceivedTime > KEEPALIVE_TIME) {
            clientAlive = false;
        }
        sleep(1);
    }
    puts("Client dead!");
    //killing threads is bad, but how else to stop receiving packets?
    if (pthread_kill(receiveThread, 0)) {
        err_exit("Keep alive thread can't kill the thread that accept keep alive packets");
    }
    //pthread_join(receiveThread, NULL);
    stopKeepAlive();
    pthread_exit(NULL);
}

void startKeepAlive() {
    clientAlive = true;
    pthread_t thread_descriptor;
    thread_pointer = &thread_descriptor;
    if (pthread_create(thread_pointer, NULL, keep_alive_thread, NULL)) {
        err_exit("Keep alive thread doesn't created");
    }
}

void sendStopKeepAlive() {
    int sockfd;
    const char *STOP_MESSAGE = "STOP";
    struct sockaddr_in     servaddr;

    // Creating socket file descriptor
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));

    // Filling server information
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(KEEPALIVE_PORT);
    servaddr.sin_addr.s_addr = INADDR_ANY;


    sendto(sockfd, STOP_MESSAGE, strlen(STOP_MESSAGE),
           MSG_CONFIRM, (const struct sockaddr *) &servaddr,
           sizeof(servaddr));

    close(sockfd);
}

void stopKeepAlive() {
    clientAlive = false;
    sendStopKeepAlive();
    close(socket_descriptor);
    tcp_stop_self();
}

bool isClientAlive() {
    return clientAlive;
}