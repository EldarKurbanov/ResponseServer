#pragma clang diagnostic ignored "-Wmissing-noreturn"
#include "broadcast.h"

int main() {

    int sock_d = broadcast_init(1031, 1032);

    while(true) {
        broadcast_send(sock_d, "Robot, where are you?", "I'm here!");
    }

}