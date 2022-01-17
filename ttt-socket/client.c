#include <stdio.h>
#include <unistd.h>
#include "arpa/inet.h"
#include <string.h>
#include <stdbool.h>

#define SIZE 3

#define WIN 100
#define DRAW 0
#define LOST -100

int minimax_for_x(char board[SIZE][SIZE], int depth, int ai_move, int *x, int *y);
int minimax_for_o(char board[SIZE][SIZE], int depth, int ai_move, int *x, int *y);
void show_board(char board[SIZE]);
void convert(char plansza[9], char board[3][3]);
int check_for_o(char board[3][3]);
int check_for_x(char board[3][3]);

int main() {

    int status, gniazdo;
    struct sockaddr_in ser;
    char buf[6], plansza[10];

    gniazdo = socket(AF_INET, SOCK_STREAM, 0);
    if (gniazdo == -1) {
        printf("Error socket ...");
        return 0;
    }

//  CONNECT
    ser.sin_family = AF_INET;
    ser.sin_port = htons(8231);
    ser.sin_addr.s_addr = inet_addr("192.168.5.21");

    status = connect(gniazdo, (struct sockaddr *) &ser, sizeof ser);
    if (status < 0) {
        printf("Connect error ..");
        return 0;
    }

//  SEND/RECEIVE
    int x, y, score, counter = 0, depth = 9;
    char player;
    char board[SIZE][SIZE];

    printf("Type START to start the game!\n");
    fgets(buf, 6, stdin);
    send(gniazdo, buf, sizeof(buf), 0);

    while (1) {

        // 1. Get board from the server
        recv(gniazdo, plansza, sizeof(plansza), 0);

        // 2. Convert board to 2d-array and print it
        convert(plansza, board);

        // 3. Check for win/lose
        if (counter != 0) {
            score = check_for_x(board);
            sleep(1);
            show_board(plansza);
        }

        if (score == WIN || score == LOST || counter == 9) {
            show_board(plansza);
            printf("Game over ...");
            buf[3] = 'e'; // e -> end
            send(gniazdo, buf, sizeof(buf), 0);
            break;
        }

        // 4. Make move
        if (counter % 2 == 0) {
            player = 'x';
            minimax_for_x(board, depth, true, &x, &y);
        } else {
            player = 'o';
            minimax_for_o(board, depth, true, &x, &y);
        }

        counter++;
        depth--;

        // 5. Clear buffer
        bzero(buf, 6);

        // 6. Fill the buffer
        buf[0] = (char) (x + 48); // -> coordinate x
        buf[1] = (char) (y + 48); // -> coordinate y
        buf[2] = player; // -> x or o
        buf[3] = 'd'; // d -> draw

        // 8. Send info to the server
        send(gniazdo, buf, strlen(buf), 0);

        // Clear buffer for plansza
        bzero(plansza, 9);
    }

    close(gniazdo);
    return 1;
}

void show_board(char board[SIZE]) {

    printf("\n");
    printf(" %c | %c | %c \n", board[0], board[1], board[2]);
    printf("---+---+---\n");
    printf(" %c | %c | %c \n", board[3], board[4], board[5]);
    printf("---+---+---\n");
    printf(" %c | %c | %c \n", board[6], board[7], board[8]);
    printf("\n");

} // Displays current situation on the board

void convert(char plansza[9], char board[3][3]) {

    for (int i = 0; i < 9; i++) {
        if (i > 2 && i < 6) {
            board[1][i - 3] = plansza[i];
        } else if (i > 5) {
            board[2][i - 6] = plansza[i];
        } else if (i < 3) {
            board[0][i] = plansza[i];
        }
    }
} // Converts recieved data to 2-d board

int check_for_x(char board[3][3]) {
    // HORIZONTAL
    if (board[0][0] == 'x' && board[0][1] == 'x' && board[0][2] == 'x') return WIN;
    if (board[1][0] == 'x' && board[1][1] == 'x' && board[1][2] == 'x') return WIN;
    if (board[2][0] == 'x' && board[2][1] == 'x' && board[2][2] == 'x') return WIN;
    // VERTICAL
    if (board[0][0] == 'x' && board[1][0] == 'x' && board[2][0] == 'x') return WIN;
    if (board[0][1] == 'x' && board[1][1] == 'x' && board[2][1] == 'x') return WIN;
    if (board[0][2] == 'x' && board[1][2] == 'x' && board[2][2] == 'x') return WIN;
    // DIAGONAL
    if (board[0][0] == 'x' && board[1][1] == 'x' && board[2][2] == 'x') return WIN;
    if (board[0][2] == 'x' && board[1][1] == 'x' && board[2][0] == 'x') return WIN;

    // ---------------------

    // HORIZONTAL
    if (board[0][0] == 'o' && board[0][1] == 'o' && board[0][2] == 'o') return LOST;
    if (board[1][0] == 'o' && board[1][1] == 'o' && board[1][2] == 'o') return LOST;
    if (board[2][0] == 'o' && board[2][1] == 'o' && board[2][2] == 'o') return LOST;
    // VERTICAL
    if (board[0][0] == 'o' && board[1][0] == 'o' && board[2][0] == 'o') return LOST;
    if (board[0][1] == 'o' && board[1][1] == 'o' && board[2][1] == 'o') return LOST;
    if (board[0][2] == 'o' && board[1][2] == 'o' && board[2][2] == 'o') return LOST;
    // DIAGONAL
    if (board[0][0] == 'o' && board[1][1] == 'o' && board[2][2] == 'o') return LOST;
    if (board[0][2] == 'o' && board[1][1] == 'o' && board[2][0] == 'o') return LOST;

    return 0;
} // Checking for win with x

int check_for_o(char board[3][3]) {
    // HORIZONTAL
    if (board[0][0] == 'x' && board[0][1] == 'x' && board[0][2] == 'x') return LOST;
    if (board[1][0] == 'x' && board[1][1] == 'x' && board[1][2] == 'x') return LOST;
    if (board[2][0] == 'x' && board[2][1] == 'x' && board[2][2] == 'x') return LOST;
    // VERTICAL
    if (board[0][0] == 'x' && board[1][0] == 'x' && board[2][0] == 'x') return LOST;
    if (board[0][1] == 'x' && board[1][1] == 'x' && board[2][1] == 'x') return LOST;
    if (board[0][2] == 'x' && board[1][2] == 'x' && board[2][2] == 'x') return LOST;
    // DIAGONAL
    if (board[0][0] == 'x' && board[1][1] == 'x' && board[2][2] == 'x') return LOST;
    if (board[0][2] == 'x' && board[1][1] == 'x' && board[2][0] == 'x') return LOST;

    // ---------------------

    // HORIZONTAL
    if (board[0][0] == 'o' && board[0][1] == 'o' && board[0][2] == 'o') return WIN;
    if (board[1][0] == 'o' && board[1][1] == 'o' && board[1][2] == 'o') return WIN;
    if (board[2][0] == 'o' && board[2][1] == 'o' && board[2][2] == 'o') return WIN;
    // VERTICAL
    if (board[0][0] == 'o' && board[1][0] == 'o' && board[2][0] == 'o') return WIN;
    if (board[0][1] == 'o' && board[1][1] == 'o' && board[2][1] == 'o') return WIN;
    if (board[0][2] == 'o' && board[1][2] == 'o' && board[2][2] == 'o') return WIN;
    // DIAGONAL
    if (board[0][0] == 'o' && board[1][1] == 'o' && board[2][2] == 'o') return WIN;
    if (board[0][2] == 'o' && board[1][1] == 'o' && board[2][0] == 'o') return WIN;

    return DRAW;
} // Checking for win with o

int minimax_for_x(char board[SIZE][SIZE], int depth, int ai_move, int *x, int *y) {

    int score, px, py, max_score, min_score, nx, ny;

    score = check_for_x(board);

    if (score == WIN || score == LOST || depth == 0) return score;

    if (ai_move) {
        for (px = 0, max_score = 10 * LOST; px < SIZE; px++) {
            for (py = 0; py < SIZE; py++) {
                if (board[px][py] == ' ') {
                    board[px][py] = 'x';
                    score = minimax_for_x(board, depth - 1, false, &nx, &ny);
                    board[px][py] = ' ';
                    if (score > max_score) {
                        max_score = score;
                        *x = px;
                        *y = py;
                    }
                }
            }
        }
        return max_score;
    } else {
        for (px = 0, min_score = 10 * WIN; px < SIZE; px++) {
            for (py = 0; py < SIZE; py++) {
                if (board[px][py] == ' ') {
                    board[px][py] = 'o';
                    score = minimax_for_x(board, depth - 1, true, &nx, &ny);
                    board[px][py] = ' ';
                    if (score < min_score) {
                        min_score = score;
                        *x = px;
                        *y = py;
                    }
                }
            }
        }
        return min_score;
    }
} // Calculates optimal move for the ai

int minimax_for_o(char board[SIZE][SIZE], int depth, int ai_move, int *x, int *y) {

    int score, px, py, max_score, min_score, nx, ny;

    score = check_for_o(board);

    if (score == WIN || score == LOST || depth == 0) return score;

    if (ai_move) {
        for (px = 0, max_score = 10 * LOST; px < SIZE; px++) {
            for (py = 0; py < SIZE; py++) {
                if (board[px][py] == ' ') {
                    board[px][py] = 'o';
                    score = minimax_for_o(board, depth - 1, false, &nx, &ny);
                    board[px][py] = ' ';
                    if (score > max_score) {
                        max_score = score;
                        *x = px;
                        *y = py;
                    }
                }
            }
        }
        return max_score;
    } else {
        for (px = 0, min_score = 10 * WIN; px < SIZE; px++) {
            for (py = 0; py < SIZE; py++) {
                if (board[px][py] == ' ') {
                    board[px][py] = 'x';
                    score = minimax_for_o(board, depth - 1, true, &nx, &ny);
                    board[px][py] = ' ';
                    if (score < min_score) {
                        min_score = score;
                        *x = px;
                        *y = py;
                    }
                }
            }
        }
        return min_score;
    }
} // Calculates optimal move for the ai
