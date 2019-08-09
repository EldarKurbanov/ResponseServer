cmake_minimum_required(VERSION 3.14)
project(ResponseServer C)

set(CMAKE_C_STANDARD 11)

add_executable(
        ResponseServer
        main.c

        network/broadcast.h
        network/broadcast.c

        lib/cJSON.c
        lib/cJSON.h

        json/control_struct.h
        json/control_struct.c
        control/process_control.h
        control/process_control.c
        control/control_hardware.h
        control/control_hardware.c
        control/control_emulate.h
#        control/control_emulate.c

        err_exit.h
        err_exit.c

        json/parse_req_res.h
        json/parse_req_res.c

        network/tcp.c
        network/tcp.h)

# wiringPi
find_library(WIRINGPI_LIBRARIES NAMES wiringPi)
target_link_libraries(ResponseServer ${WIRINGPI_LIBRARIES})
