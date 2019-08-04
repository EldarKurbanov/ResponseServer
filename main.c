#pragma clang diagnostic ignored "-Wmissing-noreturn"
#include "broadcast.h"

int main() {

    int sock_d = broadcast_init(1031, 1032);

    while(true) {
        usleep(100);
        char* client_message = broadcast_recv(sock_d);
        //check received packet and response
        if (!strcmp(client_message, "Robot, where are you?")) {
            broadcast_send("I'm here!");
            printf("Response send to %s\n", broadcast_client_addr());
            close(sock_d);
            break;
        }
    }

}