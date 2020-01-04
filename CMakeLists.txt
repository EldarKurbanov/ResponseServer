cmake_minimum_required(VERSION 3.7.2)
project(ResponseServer C)

set(CMAKE_C_STANDARD 11)

set (COMMON_FILES
        main.c

        network/broadcast.h
        network/broadcast.c
        network/tcp.c
        network/tcp.h

        lib/cJSON.c
        lib/cJSON.h

        json/control_struct.h
        json/control_struct.c
        json/parse_req_res.h
        json/parse_req_res.c

        control/process_control.h
        control/process_control.c

        security/session.c
        security/session.h

        err_exit.h
        err_exit.c

        network/keepalive.h
        network/keepalive.c
        )

link_libraries(ssl  crypto)

set (PLATFORM_FILES "")

if (__arm__)
    set(PLATFORM_FILES ${PLATFORM_FILES}
            control/control_hardware.h
            control/control_hardware.c)
else()
    set(PLATFORM_FILES ${PLATFORM_FILES}
            control/control_emulate.h
            control/control_emulate.c)
endif()

add_executable(ResponseServer ${COMMON_FILES} ${PLATFORM_FILES})

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(ResponseServer Threads::Threads)

if (__arm__)
    find_library(WIRINGPI_LIBRARIES NAMES wiringPi)
    target_link_libraries(ResponseServer ${WIRINGPI_LIBRARIES})
endif()