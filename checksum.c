#include <openssl/md5.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

static char secret_prefix[] = {
    'N', 'S', 'W', 'I', '1', '7', '7',
    'r', 'e', 's', 'u', 'b', 'm', 'i', 't',
    0x1a, 0x1b, 0xfd, 0xcf, 0xec, 0x64,
    0x17, 0xa9, 0xa3, 0x69, 0xda, 0x24,
    0x3b, 0xbe, 0xdc, 0x8e, 0xcf, 0xe0,
    0xde, 0xad, 0x5a, 0x92, 0x59, 0xab,
    0x05, 0xb6, 0xf1, 0x58, 0xf8, 0xd0
};

static char secret_suffix[] = {
    0x17, 0xa9, 0xa3, 0x69, 0xda, 0x24,
    0x92, 0x72, 0x94, 0x1b, 0x38, 0x51,
    0x3b, 0xbe, 0xdc, 0x8e, 0xcf, 0xe0,
    0xde, 0xad, 0x5a, 0x92, 0x59, 0xab,
    0x05, 0xb6, 0xf1, 0x58, 0xf8, 0xd0,
    'r', 'e', 's', 'u', 'b', 'm', 'i', 't',
    'N', 'S', 'W', 'I', '1', '7', '7'
};

#define static_sizeof(x) (sizeof(x)/sizeof(x[0]))


int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Run with single argument: your username\n");
        return 1;
    }

    int ok;
    MD5_CTX ctx;
    ok = MD5_Init(&ctx);
    if (ok != 1) {
        goto on_error;
    }

    ok = MD5_Update(&ctx, secret_prefix, static_sizeof(secret_prefix));
    if (ok != 1) {
        goto on_error;
    }

    ok = MD5_Update(&ctx, argv[1], strlen(argv[1]));
    if (ok != 1) {
        goto on_error;
    }

    ok = MD5_Update(&ctx, secret_suffix, static_sizeof(secret_suffix));
    if (ok != 1) {
        goto on_error;
    }


    unsigned char result[MD5_DIGEST_LENGTH + 1];
    ok = MD5_Final(result, &ctx);
    if (ok != 1) {
        goto on_error;
    }


    for (int i = 0; i < MD5_DIGEST_LENGTH; i++) {
        printf("%02x", (unsigned int) result[i]);
    }
    puts("");

    return 0;

on_error:
    fprintf(stderr, "Internal error, contact teachers.\n");
    return 1;
}
