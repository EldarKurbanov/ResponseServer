#pragma clang diagnostic ignored "-Wmissing-noreturn"
#include "control_struct.h"
#include "broadcast.h"

int broadcast_connect()
{
    int sock_d = broadcast_init(1031, 1032);

    while(true) {
        usleep(100);
        char *client_message = broadcast_recv(sock_d);
        //check received packet and response
        if (!strcmp(client_message, "Robot, where are you?")) {
            broadcast_send("I'm here!");
            printf("Response send to %s\n", broadcast_client_addr());
            close(sock_d);
            break;
        }
    }

    return sock_d;
}

void control_loop(int sock_d)
{
    while(true) {
        // TODO not broadcast
        char *message = broadcast_recv(sock_d);
        cJSON *control_json = cJSON_Parse(message);

        switch (get_control_type(control_json)) {
            case CONTROL_TYPE_BUTTON:
                break;
            case CONTROL_TYPE_JOYSTICK:
                break;
            case CONTROL_TYPE_PATH:
                break;
            default:
                printf("<control_loop>: Wrong control "
                               "type in client message.");
        }

    }
}

int main()
{
    int sock_d = broadcast_connect();
    control_loop(sock_d);
}

