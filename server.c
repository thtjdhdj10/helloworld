//
// main.c
// simple_server
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

#define PORT 3000
#define MAX_DATA 100

int main(int argc, const char * argv[])
{
    int ret = -1;
    struct sockaddr_in serverAddr;
    int serverSock;
    int acceptedSock;
    struct sockaddr_in clientAddr;
    char readBuf[MAX_DATA];
    ssize_t readSize;
    socklen_t clientAddrSize = sizeof(clientAddr);

    if ((serverSock = socket(PF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        goto leave;
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = (INADDR_ANY);
    serverAddr.sin_port = htons(PORT);
    if ((ret = bind(serverSock, (struct sockaddr *)&serverAddr, sizeof(serverAddr)))) {
        perror("bind");
        goto error1;
    }

    if ((ret = listen(serverSock, 1))) {
        perror("listen");
        goto error1;
    }
    acceptedSock = accept(serverSock, (struct sockaddr *)&clientAddr, &clientAddrSize);
    if (acceptedSock == -1) {
        perror("accept");
        ret = -1;
        goto error1;
    }
    if ((readSize = recv(acceptedSock, readBuf, MAX_DATA, 0)) <= 0) {
        perror("read");
        ret = -1;
    } else
        printf("Read %ld Bytes: '%s'\n", readSize, readBuf);

error2:
    close(acceptedSock);
error1:
    close(serverSock);
leave:
    return ret;
}
