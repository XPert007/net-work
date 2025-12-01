#include "../include/cns.h"

int main(){
    int serverSocketFD = createSocket();
    struct sockaddr_in *serverAddress = createAddress("", 80);
    int result = bind(serverSocketFD, serverAddress, sizeof(*serverAddress));
    if(result == 0){
        printf("socket was bound successfully\n");
    }
    listen(serverSocketFD, 10);
    struct sockaddr_in ClientAddress;
    socklen_t clientAddressSize = sizeof(ClientAddress);
    int clientSocketFD = accept(serverSocketFD, &ClientAddress, &clientAddressSize);
    char buffer[1024];
    recv(clientSocketFD, buffer, 1024, 0);
    printf("The client sent %s \n", buffer);
    return 0;
}

