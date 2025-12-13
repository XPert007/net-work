#include "../include/cns.h"

int main() {
    int socketFD = createSocket();
    if (socketFD < 0) return 1;

    printf("enter the ip, leave it empty if you are using this locally: ");
    char ip[100];
    if (!fgets(ip, sizeof(ip), stdin)) return 0;
    ip[strcspn(ip, "\n")] = 0;
    if (strlen(ip) == 0) strcpy(ip, "127.0.0.1");

    printf("enter encryption key for network (leave empty for none): ");
    char key[100];
    if (!fgets(key, sizeof(key), stdin)) return 0;
    key[strcspn(key, "\n")] = 0;

    struct sockaddr_in *address = createAddress(ip, 80);
    if (!address) { close(socketFD); return 1; }

    int result = connect(socketFD, (struct sockaddr*)address, sizeof(*address));
    if (result != 0) { free(address); close(socketFD); return 1; }
    free(address);

    while (1) {
        char message[MAX_MSG];
        printf("enter the message you would like to send: ");
        if (!fgets(message, sizeof(message), stdin)) break;

        int msglen = strlen(message);
        if (msglen == 0) continue;

        log_encrypted_hex(message);

        char enc[MAX_MSG];
        int sendlen = msglen;
        if (sendlen >= MAX_MSG) sendlen = MAX_MSG - 1;
        memcpy(enc, message, sendlen);

        if (strlen(key) > 0) xorCrypt(enc, sendlen, key);

        if (send_all(socketFD, enc, sendlen) < 0) break;

        char buffer[MAX_MSG];
        ssize_t bytes = recv(socketFD, buffer, MAX_MSG - 1, 0);
        if (bytes <= 0) break;

        if (strlen(key) > 0) xorCrypt(buffer, bytes, key);

        buffer[bytes] = 0;

        printf("server replied: %s", buffer);

        log_encrypted_hex(buffer);
    }

    close(socketFD);
    return 0;
}

