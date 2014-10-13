//
// main.c
// simple_client
//
// Created by Injae Lee on 2014. 10. 10..
// Copyright (c) 2014. Injae Lee All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define IP "127.0.0.1"
#define PORT 3000
#define WRITE_DATA "Hello World!"

int main(int argc, const char * argv[])
{
    int ret = -1;
    int clientSock;
    ssize_t writeSize;
    struct sockaddr_in serverAddr;

    if ((clientSock = socket(PF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        goto leave;
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr(IP);
    serverAddr.sin_port = htons(PORT);

    if ((ret = connect(clientSock,(struct sockaddr*)&serverAddr, sizeof(serverAddr)))) {
        perror("socket");
        goto error;
    }

    if ((writeSize = send(clientSock, WRITE_DATA, sizeof(WRITE_DATA), 0)) <= 0) {
        perror("write");
        ret = -1;
    } else
        printf("Wrote '%s' (%ld Bytes)\n", WRITE_DATA, writeSize);

error:
    close(clientSock);
leave:
    return ret;
}

