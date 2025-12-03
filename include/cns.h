#ifndef hnf_h
#define hnf_h

#include "stdio.h"
#include "sys/socket.h"
#include "netinet/in.h"
#include "arpa/inet.h"
#include "string.h"
#include "unistd.h"
#include "stdlib.h"
#include <errno.h>

#define FILE_XOR_KEY 0x5A
#define MAX_MSG 1024

void xorCrypt(char *data, int len, const char *key) {
    int klen = key ? strlen(key) : 0;
    if (klen == 0) return;
    for (int i = 0; i < len; i++)
        data[i] ^= key[i % klen];
}

void xor_single_byte_inplace(char *data, int len, char key) {
    for (int i = 0; i < len; ++i) data[i] ^= key;
}

void log_encrypted_hex(const char *text) {
    if (!text) return;
    int len = strlen(text);
    if (len == 0) return;
    char *buf = malloc(len);
    if (!buf) return;
    memcpy(buf, text, len);
    xor_single_byte_inplace(buf, len, (char)FILE_XOR_KEY);
    FILE *f = fopen("conversation.txt", "a");
    if (!f) { free(buf); return; }
    for (int i = 0; i < len; ++i) fprintf(f, "%02x", buf[i] & 0xFF);
    fprintf(f, "\n");
    fclose(f);
    free(buf);
}

int send_all(int fd, const void *buf, int len) {
    const char *p = buf;
    int left = len;
    while (left > 0) {
        int n = send(fd, p, left, 0);
        if (n < 0) {
            if (errno == EINTR) continue;
            return -1;
        }
        p += n;
        left -= n;
    }
    return len;
}

int createSocket(){
    return socket(AF_INET, SOCK_STREAM, 0);
}

struct sockaddr_in* createAddress(char* ip, int port){
    struct sockaddr_in *address = malloc(sizeof(struct sockaddr_in));
    address->sin_port = htons(port);
    address->sin_family = AF_INET;
    if(strlen(ip) == 0){
        address->sin_addr.s_addr = INADDR_ANY;
    }
    else{
        inet_pton(AF_INET, ip, &address->sin_addr.s_addr);
    }
    return address;
}

#endif

