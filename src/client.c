#include "../include/cns.h"

int main(){
    int socketFD = createSocket();
    struct sockaddr_in *address = createAddress("127.0.0.1", 80);
    int result = connect(socketFD, address, sizeof(*address));
    if(result == 0)
        printf("connection was successful\n");

    while(1){
        char message[1024];
        printf("enter the message you would like to send: ");
        fgets(message, sizeof(message), stdin);

        send(socketFD, message, strlen(message), 0);

        char buffer[1024];
        recv(socketFD, buffer, sizeof(buffer), 0);
        printf("server replied: %s", buffer);
    }

    return 0;
}

