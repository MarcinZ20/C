#include <stdio.h>
#include <unistd.h>
#include "arpa/inet.h"
#include <string.h>
#define SIZE 1024

void send_file(FILE *fp, int gniazdo);

int main() {

    int status, gniazdo;
    struct sockaddr_in ser;
    char buf[200];
    FILE *fp;
    char *filename = "file.txt";

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

    fp = fopen(filename, "r");

    if (!fp) {
        perror("Couldn't read the file ...");
        return 0;
    }

    send_file(fp, gniazdo);
    printf("Successful file transfer!");

    close(gniazdo);
    printf("Successfully closed socket!");

}

void send_file(FILE *fp, int gniazdo) {

    char data[SIZE] = {0};

    while (fgets(data, SIZE, fp)) {
        if (send(gniazdo, data, sizeof(data), 0) == -1) {
            perror("Couldn't send data ...");
            return;
        }
    }

    bzero(data, SIZE);
}