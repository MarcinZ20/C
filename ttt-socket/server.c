#include <stdio.h>
#include <unistd.h>
#include "arpa/inet.h"
#include <string.h>

void initialize_board(char board[10]);
void fill_board(int x, int y, char figure, char plansza[9]);

int main() {

    int status, socket1, socket2, length;
    struct sockaddr_in ser, cli;
    char buf[6];
    char board[9];
    char move[4];

    socket1 = socket(AF_INET, SOCK_STREAM, 0);
    if (socket1 == -1) {
        printf("Error socket1 ...");
        return 0;
    }

//  BIND
    ser.sin_family = AF_INET;
    ser.sin_port = htons(8231);
    ser.sin_addr.s_addr = inet_addr("192.168.5.21");

    status = bind(socket1, (struct sockaddr*)&ser, sizeof(ser));
    if (status < 0) {
        printf("Connect error...");
        return 0;
    }
    printf("[+] Connected!\n");

    status = listen(socket1, 10);

    if (status == -1) {
        printf("[-] Status error ...");
        return 0;
    }
    printf("[+] Listening ...\n");

    length = sizeof cli;
    socket2 = accept(socket1, (struct sockaddr*)&cli, (socklen_t*)&length);
    if (socket2 == -1) {
        printf("[-] Accept error ...");
        return 0;
    }
    printf("[+] Accepted!\n");

    recv(socket2, buf, sizeof(buf), 0);

    if (!(buf[0] == 'S' && buf[1] == 'T' && buf[2] == 'A' && buf[3] == 'R' && buf[4] == 'T')) {
        printf("Couldn't start the game ...");
        return 0;
    } else {
        initialize_board(board);
    }

    while (1) {

        // 1. Send filled board to the client
        send(socket2, board, sizeof(board), 0);

        // 2. Clear buffer for move
        bzero(move, 4);

        // 2. Receive next move
        recv(socket2, move, sizeof(move), 0);

        // 3. Check if someone won (e - end, d - draw)
        if (move[3] == 'e') {
            printf("End of the game!");
            close(socket2);
            close(socket1);
            return 0;
        }

        // 4. Print received move
        printf("x: %c\t", move[0]);
        printf("y: %c\t", move[1]);
        printf("player: %c\t", move[2]);
        printf("win: %c\n", move[3]);

        // 5. Make move and update the board
        fill_board((int) move[0], (int) move[1], move[2], board);
    }
}



void initialize_board(char board[9]) {
    for (int i = 0; i < 9; i++) {
        board[i] = ' ';
    }
//    board[9] = '\0';
}

void fill_board(int x, int y, char figure, char plansza[9]) {

    /*    0 1 2
     *  0 0 1 2
     *  1 3 4 5
     *  2 6 7 8
     * */
    if (x == '0') {
        plansza[y - 48] = figure;
    } else if (x == '1') {
        plansza[y + 3 - 48] = figure;
    } else if (x == '2') {
        plansza[y + 6 - 48] = figure;
    }
}
