#include <stdio.h>
#include <unistd.h>
#include "arpa/inet.h"
#include <string.h>

int main() {

    int status, gniazdo;
    struct sockaddr_in ser;
    char buf[200];

    gniazdo = socket(AF_INET,SOCK_STREAM,0);
    if (gniazdo == -1) {
        printf("Error socket ...");
        return 0;
    }

//    CONNECT
    ser.sin_family = AF_INET;
    ser.sin_port = htons(80);
    ser.sin_addr.s_addr = inet_addr("99.83.207.202");

    printf("Podaj tekst:");
    fgets(buf,sizeof buf, stdin);

    status = connect(gniazdo, (struct sockaddr*)&ser, sizeof ser);
    if (status < 0) {
        printf("Error connect ...");
        return 0;
    }
//    SEND/RECEIVE
    status = send(gniazdo, buf, strlen(buf), 0);
    status = recv(gniazdo, buf, (sizeof buf) - 1, 0);
    buf[status]='\0';
    printf("I got: %s\n", buf);
    close(gniazdo);


//    SERVER
    int status, gniazdo, gniazdo2, dlugosc, nr = 1, end = 1;
    struct sockaddr_in ser, cli;
    char buf[200];

    gniazdo = socket(AF_INET,SOCK_STREAM,0);
    if (gniazdo == -1) {
        printf("Error socket ...");
        return 0;
    }

//    BIND
    ser.sin_family = AF_INET;
    ser.sin_port = htons(8231);
    ser.sin_addr.s_addr = inet_addr("10.128.12.167");

    status = bind(gniazdo, (struct sockaddr*)&ser, sizeof(ser));
    if (status < 0) {
        printf("Error connect ...");
        return 0;
    }

    status = listen(gniazdo, 10);
    if (status == -1) {
        printf("status error ...");
        return 0;
    }

    while (end) {
        dlugosc = sizeof cli;
        gniazdo2 = accept(gniazdo,(struct sockaddr*)&cli, (socklen_t*)&dlugosc);
        if (gniazdo2 == -1) {
            printf("Eroor accept ...");
            return 0;
        }
        status = recv(gniazdo2, buf, sizeof buf, 0);

        if (buf[0] == 'Q') {
            sprintf(buf, "OK, END OF WORK");
            end = 0;
            close(gniazdo2);
        } else if (buf[0] == 'N') {
            sprintf(buf, "You are %d in line!", nr++);
        } else {
            sprintf(buf, "I don't understand the question ...");
        }
        status = send(gniazdo2, buf, strlen(buf), 0);
    }

    close(gniazdo);
    return 0;
}
