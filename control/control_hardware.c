//
// Created by mrkotyk on 05.08.2019.
//
#include "control_hardware.h"

void control_hardware_init() {
    wiringPiSetup();
}

void set_pins(int v0,  int v1,  int v2,  int v3,  int v4,  int v5,  int v6,
              int v7,  int v8,  int v9,  int v10, int v11, int v12, int v13,
              int v14, int v15, int v16, int v17, int v18, int v19, int v20) {
    pinMode (0,  v0);  pinMode (1,  v1);  pinMode (2,  v2);
    pinMode (3,  v3);  pinMode (4,  v4);  pinMode (5,  v5);
    pinMode (6,  v6);  pinMode (7,  v7);  pinMode (8,  v8);
    pinMode (9,  v9);  pinMode (10, v10); pinMode (11, v11);
    pinMode (12, v12); pinMode (13, v13); pinMode (14, v14);
    pinMode (15, v15); pinMode (16, v16); pinMode (17, v17);
    pinMode (18, v18); pinMode (19, v19); pinMode (20, v20);
}

void set_pins_arr(int* arr, int n) {
    for (int i = 0; i < n; ++i) {
        pinMode(0, arr[i]);
    }
}

