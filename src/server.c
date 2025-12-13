#include "../include/cns.h"

int main(){
    int serverSocketFD = createSocket();
    struct sockaddr_in *serverAddress = createAddress("0.0.0.0", 80);
    int result = bind(serverSocketFD, serverAddress, sizeof(*serverAddress));
    if(result == 0)
        printf("socket was bound successfully\n");

    listen(serverSocketFD, 10);

    struct sockaddr_in ClientAddress;
    socklen_t clientAddressSize = sizeof(ClientAddress);
    int clientSocketFD = accept(serverSocketFD, &ClientAddress, &clientAddressSize);

    while(1){
        char buffer[1024];
        recv(clientSocketFD, buffer, sizeof(buffer), 0);
        printf("The client sent: %s", buffer);

        char reply[1024];
        printf("enter reply: ");
        fgets(reply, sizeof(reply), stdin);

        send(clientSocketFD, reply, strlen(reply), 0);
    }

    return 0;
}

