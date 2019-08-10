//
// Created by mrkotyk on 10.08.2019.
//
#include "session.h"
#include "../err_exit.h"

static int init_flag = 0;

void security_init() {
    // set cur time as seed
    srand48(time(NULL));
    init_flag = 1;
}

char* generate_session_key()
{
    if(!init_flag) err_exit("security module has not been initialized.");
    return rand_str(SESSION_KEY_LENGTH);
}

char *rand_str(size_t length) {
    if(!length) return "";

    char *str = malloc(length + 1);
    if(!str) return "";

    for (size_t n = 0; n < length; n++) {
        size_t key = (size_t) ( drand48() * strlen(ALPHABET) );
        str[n] = ALPHABET[key];
    }
    str[length] = '\0';

    return str;
}

char *rsa()
{
    BIGNUM *kExp = BN_new();
    BN_set_word(kExp, RSA_F4);

    RSA *rsa = RSA_new();
    RSA_generate_key_ex(rsa, RSA_BITS, kExp, NULL);

    /* To get the C-string PEM form: */
    BIO *bio = BIO_new(BIO_s_mem());
    PEM_write_bio_RSAPrivateKey(bio, rsa, NULL, NULL, 0, NULL, NULL);

    int key_len = BIO_pending(bio);
    char *pem_key = calloc(key_len + 1, 1); /* Null-terminate */
    BIO_read(bio, pem_key, key_len);

    BIO_free_all(bio);
    RSA_free(rsa);
    free(pem_key);

    return pem_key;
}

char *base64(const unsigned char *input, int length)
{
    BIO *bmem, *b64;
    BUF_MEM *bptr;

    b64 = BIO_new(BIO_f_base64());
    bmem = BIO_new(BIO_s_mem());
    b64 = BIO_push(b64, bmem);
    BIO_write(b64, input, length);
    BIO_flush(b64);
    BIO_get_mem_ptr(b64, &bptr);

    char *buff = (char *)malloc(bptr->length);
    memcpy(buff, bptr->data, bptr->length-1);
    buff[bptr->length-1] = 0;

    BIO_free_all(b64);

    return buff;
}