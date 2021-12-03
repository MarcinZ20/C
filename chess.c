#include <stdio.h>

#define LOST -1000
#define WIN 1000
#define EMPTY 12

#define SIZE 8

#define TRUE 1
#define FALSE 0

int MAX_DIR[] = {8,8,4,4,8,3,8,8,4,4,8,3,0};
int MAX_DIS[] = {2,8,8,8,2,2,2,8,8,8,2,2,0};
int WX[12][8] = {{0,1,1,1,0,-1,-1,-1},{0,1,1,1,0,-1,-1,-1},{0,1,0,-1},{1,1,-1,-1},{1,2,2,1,-1,-2,-2,-1},{-1,0,1},
               {0,1,1,1,0,-1,-1,-1},{0,1,1,1,0,-1,-1,-1},{0,1,0,-1},{1,1,-1,-1},{1,2,2,1,-1,-2,-2,-1},{-1,0,1} };

int WY[12][8]={{-1,-1,0,1,1,1,0,-1},{-1,-1,0,1,1,1,0,-1},{-1,0,1,0},{-1,1,1,-1},{-2,-1,1,2,2,1,-1,-2},{-1,-1,-1},
               {-1,-1,0,1,1,1,0,-1},{-1,-1,0,1,1,1,0,-1},{-1,0,1,0},{-1,1,1,-1},{-2,-1,1,2,2,1,-1,-2},{1,1,1} };

int minimax(int board[SIZE][SIZE], int depth, int ai_move, int *x, int *y, int *end_dir, int *end_dis);
void show_board(int p[SIZE][SIZE]);
int rate_board(int board[SIZE][SIZE]);

int main() {

    int board[8][8] = {{2, 5, 12, 12, 12, 12, 11, 8},
                       {4, 5, 12, 12, 12, 12, 11, 10},
                       {3, 5, 12, 12, 12, 12, 11, 9},
                       {0, 5, 12, 12, 12, 12, 11, 7},
                       {1, 5, 12, 12, 12, 12, 11, 6},
                       {3, 5, 12, 12, 12, 12, 11, 9},
                       {4, 5, 12, 12, 12, 12, 11, 10},
                       {2, 5, 12, 12, 12, 12, 11, 8}};

    int x_start, y_start, x_end, y_end, x, y, k, o, dx, dy, result;

    while (1) {

        minimax(board, 5, TRUE, &x, &y, &k, &o);
        dx = o * WX[board[x][y]][k];
        dy = o * WY[board[x][y]][k];

        result = rate_board(board);

        if (result == WIN || result == LOST) return 1;

        board[x+dx][y+dy] = board[x][y];
        board[x][y] = EMPTY;

        show_board(board);

        printf("\n");
        printf("Start coordinates: \t");
        scanf("%d %d", &x_start, &y_start);
        printf("\n");
        printf("End coordinates: \t");
        scanf("%d %d", &x_end, &y_end);

        board[x_end][y_end] = board[x_start][y_start];
        board[x_start][y_start] = EMPTY;
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

int minimax(int board[SIZE][SIZE], int depth, int ai_move, int *x, int *y, int *end_dir, int *end_dis) {

    int px_pom, py_pom, dir_pom, dis_pom, px, py, w_max, w_min, dir, dis, dx, dy, fig_move, take_fig, result;

    result = rate_board(board);

    if (result == WIN || result == LOST) return result;

    if (ai_move) {
        for (px = 0, w_max = 100 * LOST; px < SIZE; px++) {
            for (py = 0; py < SIZE; py++) {
                if (board[px][py] > 5 && board[px][py] < 12) {
                    for (dir = 0; dir < MAX_DIR[board[px][py]]; dir++) {
                        for (dis = 0; dis < MAX_DIS[board[px][py]]; dis++) {
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
                                        result = minimax(board, depth - 1, FALSE, &px_pom, &py_pom, &dir_pom,
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
        for (px = 0, w_min = 100 * WIN; px < SIZE; px++) {
            for (py = 0; py < SIZE; py++) {
                if (board[px][py] <= 5) {
                    for (dir = 0; dir < MAX_DIR[board[px][py]]; dir++) {
                        for (dis = 0; dis < MAX_DIS[board[px][py]]; dis++) {
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
                                        result = minimax(board, depth - 1, TRUE, &px_pom, &py_pom, &dir_pom, &dis_pom);
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

    //przyjmując: 0-król, 1-hetman, 2-wieża, 3-goniec, 4-skoczek, 5-pionek,
    //            6-król_k, 7-hetman_k, 8-wieża_k, 9-goniec_k, 10-skoczek_k, 11-pionek_k,
    //            12-pole puste

    char fig[13] = {'k', 'h', 'w', 'g', 's', 'p', 'K', 'H', 'W', 'G', 'S', 'P', ' '};

    printf("+---+---+---+---+---+---+---+---+\n");
    printf("| %c | %c | %c | %c | %c | %c | %c | %c |\n", fig[p[0][0]], fig[p[0][1]], fig[p[0][2]], fig[p[0][3]], fig[p[0][4]], fig[p[0][5]], fig[p[0][6]], fig[p[0][7]]);
    printf("+---+---+---+---+---+---+---+---+\n");
    printf("| %c | %c | %c | %c | %c | %c | %c | %c |\n", fig[p[1][0]], fig[p[1][1]], fig[p[1][2]], fig[p[1][3]], fig[p[1][4]], fig[p[1][5]], fig[p[1][6]], fig[p[1][7]]);
    printf("+---+---+---+---+---+---+---+---+\n");
    printf("| %c | %c | %c | %c | %c | %c | %c | %c |\n", fig[p[2][0]], fig[p[2][1]], fig[p[2][2]], fig[p[2][3]], fig[p[2][4]], fig[p[2][5]], fig[p[2][6]], fig[p[2][7]]);
    printf("+---+---+---+---+---+---+---+---+\n");
    printf("| %c | %c | %c | %c | %c | %c | %c | %c |\n", fig[p[3][0]], fig[p[3][1]], fig[p[3][2]], fig[p[3][3]], fig[p[3][4]], fig[p[3][5]], fig[p[3][6]], fig[p[3][7]]);
    printf("+---+---+---+---+---+---+---+---+\n");
    printf("| %c | %c | %c | %c | %c | %c | %c | %c |\n", fig[p[4][0]], fig[p[4][1]], fig[p[4][2]], fig[p[4][3]], fig[p[4][4]], fig[p[4][5]], fig[p[4][6]], fig[p[4][7]]);
    printf("+---+---+---+---+---+---+---+---+\n");
    printf("| %c | %c | %c | %c | %c | %c | %c | %c |\n", fig[p[5][0]], fig[p[5][1]], fig[p[5][2]], fig[p[5][3]], fig[p[5][4]], fig[p[5][5]], fig[p[5][6]], fig[p[5][7]]);
    printf("+---+---+---+---+---+---+---+---+\n");
    printf("| %c | %c | %c | %c | %c | %c | %c | %c |\n", fig[p[6][0]], fig[p[6][1]], fig[p[6][2]], fig[p[6][3]], fig[p[6][4]], fig[p[6][5]], fig[p[6][6]], fig[p[6][7]]);
    printf("+---+---+---+---+---+---+---+---+\n");
    printf("| %c | %c | %c | %c | %c | %c | %c | %c |\n", fig[p[7][0]], fig[p[7][1]], fig[p[7][2]], fig[p[7][3]], fig[p[7][4]], fig[p[7][5]], fig[p[7][6]], fig[p[7][7]]);
    printf("+---+---+---+---+---+---+---+---+\n");

}

// TODO: kopiowanie, usunięcie elementów, dopisanie elementu, wypisanie drzewa, znajdź wartość, stworzenie drzew,
//  zwolnienie pamięci

