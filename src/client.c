#include "../include/cns.h"
#include <string.h>

int main(){
    int socketFD = createSocket();

    printf("enter the ip, leave it empty if you are using this locally: ");
    char ip[100];
    fgets(ip, sizeof(ip), stdin);
    ip[strcspn(ip, "\n")] = 0;

    if(strlen(ip) == 0)
        strcpy(ip, "127.0.0.1");

    struct sockaddr_in *address = createAddress(ip, 80);
    int result = connect(socketFD, address, sizeof(*address));
    if(result == 0)
        printf("connection was successful\n");

    while(1){
        char message[1024];
        printf("enter the message you would like to send: ");
        fgets(message, sizeof(message), stdin);

        send(socketFD, message, strlen(message), 0);

        char buffer[1024];
        int bytes = recv(socketFD, buffer, sizeof(buffer)-1, 0);
        if(bytes <= 0)
            break;
        buffer[bytes] = 0;

        printf("server replied: %s", buffer);
    }

    return 0;
}


