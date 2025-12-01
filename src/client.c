#include "../include/cns.h"
int main(){
    int socketFD = createSocket();
    struct sockaddr_in *address = createAddress("127.0.0.1", 80);
    int result = connect(socketFD,(struct sockaddr*)address, sizeof(*address)); 
    if(result == 0)
        printf("connection was successful");
    char* message;
    message = "hello avi";
    send(socketFD,message, strlen(message),0);

    return 0;
}

