#include "broadcast.h"

int main() {

    int sock_d = broadcast_init(1031, 1032);

    broadcast_send(sock_d, "Robot, where are you?", "I'm here!");

    close(sock_d);

}