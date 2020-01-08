//
// Created by mrkotyk on 10.08.2019.
//

#ifndef RESPONSESERVER_SESSION_H
#define RESPONSESERVER_SESSION_H

// 20 76
#define ALPHABET "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define SESSION_KEY_LENGTH 25
#define RSA_BITS 1024

#include <openssl/ssl.h>
#include <openssl/rsa.h>
#include <openssl/evp.h>
#include <openssl/pem.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char* session_key;

void security_init();

char* generate_session_key();

char *base64(const unsigned char *input, int length);

char *rsa();

char *rand_str(size_t length);

#endif //RESPONSESERVER_SESSION_H
