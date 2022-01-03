#include <stdio.h>
#include <unistd.h>
#include "arpa/inet.h"
#include <string.h>

#define SIZE 200

void clear_buffer(char *buffer);

int main() {
    int status, socket1, socket2, length;
    struct sockaddr_in ser, cli;
    char buf[SIZE];

    socket1 = socket(AF_INET, SOCK_STREAM, 0);
    if (socket1 == -1) {
        printf("Error socket1 ...");
        return 0;
    }

//    BIND
    ser.sin_family = AF_INET;
    ser.sin_port = htons(8231);
    ser.sin_addr.s_addr = inet_addr("192.168.5.21");

    status = bind(socket1, (struct sockaddr*)&ser, sizeof(ser));
    if (status < 0) {
        printf("Connect error...");
        return 0;
    }

    status = listen(socket1, 10);
    if (status == -1) {
        printf("Status error ...");
        return 0;
    }

    length = sizeof cli;
    socket2 = accept(socket1, (struct sockaddr*)&cli, (socklen_t*)&length);
    if (socket2 == -1) {
        printf("Accept error ...");
        return 0;
        }

    while (1) {
        clear_buffer(buf);
        status = recv(socket2, buf, sizeof(buf), 0);
        buf[status] = '\0';

        if (buf[0] == 'Q') {
            close(socket2);
            printf("Client has been disconnected!");
            break;
        }

        printf("Client: %s", buf);
        printf("Message: ");
        fgets(buf, SIZE, stdin);
        send(socket2, buf, strlen(buf), 0);

        if (*buf == 'Q') {
            close(socket2);
            break;
        }
    }
    close(socket1);
    return 0;
}

void clear_buffer(char *buffer) {
    // while (*buffer) {
    //     *buffer++ = '\0';
    // }
    bzero(buffer, SIZE);
}