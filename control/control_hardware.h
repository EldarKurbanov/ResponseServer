//
// Created by mrkotyk on 05.08.2019.
//

#ifndef RESPONSESERVER_CONTROL_HARDWARE_H
#define RESPONSESERVER_CONTROL_HARDWARE_H

#define DELAY_TIME 500

// Заголовок подключается только если определена переменная
// окружения __arm__, в ином случае происходит подключение
// заголовка control_emulate.h, в котором вызов
// методов движения просто выводит их названия в консоль
// (см control_emulate.h)
#include <wiringPi.h>
#include "../err_exit.h"

void control_hardware_setup_pins();

extern void control_init();

void control_forward();

void control_back();

void control_rotate_left();

void control_rotate_right();

void control_left_forward();

void control_right_forward();

#endif //RESPONSESERVER_CONTROL_HARDWARE_H