#include "../include/cns.h"
int main(){
    int socketFD = createSocket();
    struct sockaddr_in *address = createAddress("8.8.8.8", 80);
    int result = connect(socketFD,(struct sockaddr*)address, sizeof(*address)); 
    if(result == 0)
        printf("connection was successful");
    char* buffer;
    buffer = "";
    send(socketFD,buffer, strlen(buffer),0);

    return 0;
}

