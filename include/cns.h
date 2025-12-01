#ifndef hnf_h
#define hnf_h

#include "stdio.h"
#include "sys/socket.h"
#include "netinet/in.h"
#include "arpa/inet.h"
#include "string.h"
#include "unistd.h"
#include "stdlib.h"
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
    inet_pton(AF_INET, ip,&address->sin_addr.s_addr);
    }
    return address;
}
#endif

