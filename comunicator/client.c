#include <stdio.h>
#include <unistd.h>
#include "arpa/inet.h"
#include <string.h>

#define SIZE 200

void clear_buffer(char *buffer);

int main() {

    int status, gniazdo;
    struct sockaddr_in ser;
    char buf[SIZE];

    gniazdo = socket(AF_INET,SOCK_STREAM,0);
    if (gniazdo == -1) {
        printf("Error socket ...");
        return 0;
    }

//    CONNECT
    ser.sin_family = AF_INET;
    ser.sin_port = htons(8231);
    ser.sin_addr.s_addr = inet_addr("192.168.5.21");

    status = connect(gniazdo, (struct sockaddr*)&ser, sizeof ser);
    if (status < 0) {
        printf("Connect error ..");
        return 0;
    }
//    SEND/RECEIVE

    while (1) {
        printf("Message: ");
        fgets(buf, SIZE, stdin);
        send(gniazdo, buf, strlen(buf), 0);

        if (*buf == 'Q') {
            printf("Disconnected");
            break;
        }

        clear_buffer(buf);
        status = recv(gniazdo, buf, sizeof(buf), 0);
        buf[status] = '\0';

        if (*buf == 'Q') {
            printf("Server has been disconnected!");
            break;
        }

        printf("Server: %s", buf);
    }
    close(gniazdo);
    return 0;
}

void clear_buffer(char *buffer) {
    // while (*buffer) {
    //     *buffer++ = '\0';
    // }
    bzero(buffer, SIZE)
}