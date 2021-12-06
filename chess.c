#include <stdio.h>
#include <stdbool.h>

#define LOST (-1000)
#define WIN 1000
#define EMPTY 12

#define SIZE 8

int MAX_DIR[] = {8,8,4,4,8,3,8,8,4,4,8,3,0};
int MAX_DIS[] = {2,8,8,8,2,2,2,8,8,8,2,2,0};
int WX[12][8] = {{0,1,1,1,0,-1,-1,-1},{0,1,1,1,0,-1,-1,-1},{0,1,0,-1},{1,1,-1,-1},{1,2,2,1,-1,-2,-2,-1},{-1,0,1},
               {0,1,1,1,0,-1,-1,-1},{0,1,1,1,0,-1,-1,-1},{0,1,0,-1},{1,1,-1,-1},{1,2,2,1,-1,-2,-2,-1},{-1,0,1}};

int WY[12][8]={{-1,-1,0,1,1,1,0,-1},{-1,-1,0,1,1,1,0,-1},{-1,0,1,0},{-1,1,1,-1},{-2,-1,1,2,2,1,-1,-2},{1,1,1},
               {-1,-1,0,1,1,1,0,-1},{-1,-1,0,1,1,1,0,-1},{-1,0,1,0},{-1,1,1,-1},{-2,-1,1,2,2,1,-1,-2},{-1,-1,- 1}};

int minimax(int board[SIZE][SIZE], int depth, bool ai_move, int *x, int *y, int *end_dir, int *end_dis);
int rate_board(int board[SIZE][SIZE]);
void show_board(int p[SIZE][SIZE]);
void players_move(char *x1, char *x2, char *y1, char *y2);

int main() {

    int x, y, dir, dis, dx, dy, result;
    char x1, x2, y1, y2;

    int board[8][8] = {{2, 5, 12, 12, 12, 12, 11, 8},
                       {4, 5, 12, 12, 12, 12, 11, 10},
                       {3, 5, 12, 12, 12, 12, 11, 9},
                       {0, 5, 12, 12, 12, 12, 11, 7},
                       {1, 5, 12, 12, 12, 12, 11, 6},
                       {3, 5, 12, 12, 12, 12, 11, 9},
                       {4, 5, 12, 12, 12, 12, 11, 10},
                       {2, 5, 12, 12, 12, 12, 11, 8}};

    while (true) {

        minimax(board, 6, true, &x, &y, &dir, &dis);
        dx = dis * WX[board[x][y]][dir];
        dy = dis * WY[board[x][y]][dir];

        board[x+dx][y+dy] = board[x][y];
        board[x][y] = EMPTY;

        result = rate_board(board);

        if (2 * result >= WIN) {
            printf("You lost ...");
            return 1;
        } else if (2 * result <= LOST) {
            printf("You won!");
            return 0;
        }

        show_board(board);

        players_move(&x1, &x2, &y1, &y2);
        board[x2-97][y2-49] = board[x1-97][y1-49]; // ASCI MAGIC
        board[x1-97][y1-49] = EMPTY;

        result = rate_board(board);

        if (2 * result >= WIN) {
            printf("You lost ...");
            return 1;
        } else if (2 * result <= LOST) {
            printf("You won!");
            return 0;
        }
        show_board(board);
    }
}

int rate_board(int board[SIZE][SIZE]) {

    int result = 0;

    int rates[13] = {LOST, -9, -5, -4, -3, -1, WIN, 9, 5, 4, 3, 1, 0};

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            result += rates[board[i][j]];
        }
    }
    return result;
}

int minimax(int board[SIZE][SIZE], int depth, bool ai_move, int *x, int *y, int *end_dir, int *end_dis) {

    int px_pom, py_pom, dir_pom, dis_pom, px, py, w_max, w_min, dir, dis, dx, dy, fig_move, take_fig, result;

    result = rate_board(board);

    if (2 * result >= WIN || 2 * result <= LOST || depth == 0) return result;

    if (ai_move) {
        for (px = 0, w_max = 10 * LOST; px < SIZE; px++) {
            for (py = 0; py < SIZE; py++) {
                if (board[px][py] > 5 && board[px][py] < 12) {
                    for (dir = 0; dir < MAX_DIR[board[px][py]]; dir++) {
                        for (dis = 1; dis < MAX_DIS[board[px][py]]; dis++) {
                            dx = (dis - 1) * WX[board[px][py]][dir];
                            dy = (dis - 1) * WY[board[px][py]][dir];
                            if (dis >= 2 && board[px + dx][py + dy] != EMPTY) break;
                            dx = dis * WX[board[px][py]][dir];
                            dy = dis * WY[board[px][py]][dir];
                            if (px + dx >= 0 && px + dx < 8 && py + dy >= 0 && py + dy < 8) {
                                if (board[px + dx][py + dy] == EMPTY || board[px + dx][py + dy] <= 5) {
                                    if ((board[px][py] != 11) ||
                                        (board[px + dx][py + dy] == EMPTY && dx == 0) ||
                                        (board[px + dx][py + dy] != EMPTY && dx != 0)) {
                                        fig_move = board[px][py];
                                        take_fig = board[px + dx][py + dy];
                                        board[px + dx][py + dy] = board[px][py];
                                        board[px][py] = EMPTY;
                                        if (board[px + dx][py + dy] == 11 && py + dy == 7) {
                                            board[px + dx][py + dy] = 7;
                                        }
                                        result = minimax(board, depth - 1, false, &px_pom, &py_pom, &dir_pom,
                                                         &dis_pom);
                                        board[px][py] = fig_move;
                                        board[px + dx][py + dy] = take_fig;
                                        if (result > w_max) {
                                            w_max = result;
                                            *x = px;
                                            *y = py;
                                            *end_dir = dir;
                                            *end_dis = dis;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        } return w_max;
    } else {
        for (px = 0, w_min = 10 * WIN; px < SIZE; px++) {
            for (py = 0; py < SIZE; py++) {
                if (board[px][py] <= 5) {
                    for (dir = 0; dir < MAX_DIR[board[px][py]]; dir++) {
                        for (dis = 1; dis < MAX_DIS[board[px][py]]; dis++) {
                            dx = (dis - 1) * WX[board[px][py]][dir];
                            dy = (dis - 1) * WY[board[px][py]][dir];
                            if (dis >= 2 && board[px + dx][py + dy] != EMPTY) break;
                            dx = dis * WX[board[px][py]][dir];
                            dy = dis * WY[board[px][py]][dir];
                            if (px + dx >= 0 && px + dx < 8 && py + dy >= 0 && py + dy < 8) {
                                if (board[px + dx][py + dy] >= 6) {
                                    if ((board[px][py] != 5) ||
                                        (board[px + dx][py + dy] == EMPTY && dx == 0) ||
                                        (board[px + dx][py + dy] != EMPTY && dx != 0)) {
                                        fig_move = board[px][py];
                                        take_fig = board[px + dx][py + dy];
                                        board[px + dx][py + dy] = board[px][py];
                                        board[px][py] = EMPTY;
                                        if (board[px + dx][py + dy] == 5 && py + dy == 0) {
                                            board[px + dx][py + dy] = 1;
                                        }
                                        result = minimax(board, depth - 1, true, &px_pom, &py_pom, &dir_pom, &dis_pom);
                                        board[px][py] = fig_move;
                                        board[px + dx][py + dy] = take_fig;
                                        if (result < w_min) {
                                            w_min = result;
                                            *x = px;
                                            *y = py;
                                            *end_dir = dir;
                                            *end_dis = dis;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        } return w_min;
    }
}

void show_board(int p[SIZE][SIZE]) {

    char fig[13] = {'k', 'h', 'w', 'g', 's', 'p', 'K', 'H', 'W', 'G', 'S', 'P', ' '};

    printf("    1   2   3   4   5   6   7   8\n");
    printf("  +---+---+---+---+---+---+---+---+\n");
    printf("a | %c | %c | %c | %c | %c | %c | %c | %c |\n", fig[p[0][0]], fig[p[0][1]], fig[p[0][2]], fig[p[0][3]],
           fig[p[0][4]], fig[p[0][5]], fig[p[0][6]], fig[p[0][7]]);
    printf("  +---+---+---+---+---+---+---+---+\n");
    printf("b | %c | %c | %c | %c | %c | %c | %c | %c |\n", fig[p[1][0]], fig[p[1][1]], fig[p[1][2]], fig[p[1][3]],
           fig[p[1][4]], fig[p[1][5]], fig[p[1][6]], fig[p[1][7]]);
    printf("  +---+---+---+---+---+---+---+---+\n");
    printf("c | %c | %c | %c | %c | %c | %c | %c | %c |\n", fig[p[2][0]], fig[p[2][1]], fig[p[2][2]], fig[p[2][3]],
           fig[p[2][4]], fig[p[2][5]], fig[p[2][6]], fig[p[2][7]]);
    printf("  +---+---+---+---+---+---+---+---+\n");
    printf("d | %c | %c | %c | %c | %c | %c | %c | %c |\n", fig[p[3][0]], fig[p[3][1]], fig[p[3][2]], fig[p[3][3]],
           fig[p[3][4]], fig[p[3][5]], fig[p[3][6]], fig[p[3][7]]);
    printf("  +---+---+---+---+---+---+---+---+\n");
    printf("e | %c | %c | %c | %c | %c | %c | %c | %c |\n", fig[p[4][0]], fig[p[4][1]], fig[p[4][2]], fig[p[4][3]],
           fig[p[4][4]], fig[p[4][5]], fig[p[4][6]], fig[p[4][7]]);
    printf("  +---+---+---+---+---+---+---+---+\n");
    printf("f | %c | %c | %c | %c | %c | %c | %c | %c |\n", fig[p[5][0]], fig[p[5][1]], fig[p[5][2]], fig[p[5][3]],
           fig[p[5][4]], fig[p[5][5]], fig[p[5][6]], fig[p[5][7]]);
    printf("  +---+---+---+---+---+---+---+---+\n");
    printf("g | %c | %c | %c | %c | %c | %c | %c | %c |\n", fig[p[6][0]], fig[p[6][1]], fig[p[6][2]], fig[p[6][3]],
           fig[p[6][4]], fig[p[6][5]], fig[p[6][6]], fig[p[6][7]]);
    printf("  +---+---+---+---+---+---+---+---+\n");
    printf("h | %c | %c | %c | %c | %c | %c | %c | %c |\n", fig[p[7][0]], fig[p[7][1]], fig[p[7][2]], fig[p[7][3]],
           fig[p[7][4]], fig[p[7][5]], fig[p[7][6]], fig[p[7][7]]);
    printf("  +---+---+---+---+---+---+---+---+\n");
}

void players_move(char *x1, char *x2, char *y1, char *y2) {

    char user_input[20];
    printf("Your move:");
    fgets(user_input, 19, stdin);
    sscanf(user_input, "%c%c %c%c", x1, y1, x2, y2);
}
