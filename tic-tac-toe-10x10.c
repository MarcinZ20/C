#include <stdio.h>

#define SIZE 10

#define TRUE 1
#define FALSE 0

#define WIN 100
#define DRAW 0
#define LOST -100

void show_board(char board[SIZE][SIZE]);
int rate_situation(char board[SIZE][SIZE]);
int minimax(char board[SIZE][SIZE], int depth, int ai_move, int *x, int *y);
int move_validation(char board[SIZE][SIZE], int x, int y);

int main(void) {

    int x, y, score, counter = 0, depth = 3;
    char board[SIZE][SIZE];

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = ' ';
        }
    }

    while (1) {

        minimax(board, depth, TRUE, &x, &y);
        board[x][y] = 'x';
        show_board(board);
        score = rate_situation(board);

        if (score == WIN) {
            printf("You lost ... \n");
            return 1;
        } else if (score == LOST) {
            printf("You won ... impossible!\n");
            return -1;
        }

        printf("Your move: ");
        scanf("%d %d", &x, &y);

        while (!move_validation(board, x, y)) {
            printf("Invalid move - try again: ");
            scanf("%d %d", &x, &y);
        }

        board[x][y] = 'o';
        show_board(board);
        score = rate_situation(board);
        counter += 2;

        if (score == WIN) {
            printf("You lost ...");
            return 1;
        } else if (score == LOST) {
            printf("You won!");
            return 1;
        } else if (counter == 100) {
            printf("It's a draw - good job!\n");
            return 0;
        }
    }
}

int rate_situation(char board[SIZE][SIZE])  {

    // Horizontal
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j <= SIZE/2; j++) {
            if (board[i][j] == 'x' && board[i][j+1] == 'x' && board[i][j+2] == 'x' && board[i][j+3] == 'x' && board[i][j+4] == 'x') return WIN;
        }
    }

    // Vertical
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j <= SIZE/2; j++) {
            if (board[j][i] == 'x' && board[j+1][i] == 'x' && board[j+2][i] == 'x' && board[j+3][i] == 'x' && board[j+4][i] == 'x') return WIN;
        }
    }

    // Diagonal '\'
    for (int i = 0; i <= SIZE/2; i++) {
        for (int j = 0; j < SIZE/2 + 1; j++) {
            if (board[j][i] == 'x' && board[j+1][i+1] == 'x' && board[j+2][i+2] == 'x' && board[j+3][i+3] == 'x' && board[j+4][i+4] == 'x') return WIN;
        }
    }

    // Diagonal '/'
    for (int i = 0; i <= SIZE/2; i++) {
        for (int j = SIZE/2 - 1; j < SIZE; j++) {
            if (board[i][j] == 'x' && board[i+1][j-1] == 'x' && board[i+2][j-2] == 'x' && board[i+3][j-3] == 'x' &&
            board[i+4][j-4] == 'x') return WIN;
        }
    }

    // --------------------------------------------------------------------------------

    // Horizontal
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE/2; j++) {
            if (board[i][j] == 'o' && board[i][j+1] == 'o' && board[i][j+2] == 'o' && board[i][j+3] == 'o' && board[i][j+4] == 'o') return LOST;
        }
    }

    // Vertical
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE/2; j++) {
            if (board[j][i] == 'o' && board[j+1][i] == 'o' && board[j+2][i] == 'o' && board[j+3][i] == 'o' && board[j+4][i] == 'o') return LOST;
        }
    }

    // Diagonal '\'
    for (int i = 0; i <= SIZE/2; i++) {
        for (int j = 0; j < SIZE/2 + 1; j++) {
            if (board[j][i] == 'o' && board[j+1][i+1] == 'o' && board[j+2][i+2] == 'o' && board[j+3][i+3] == 'o' && board[j+4][i+4] == 'o') return LOST;
        }
    }

    // Diagonal '/'
    for (int i = 0; i <= SIZE/2; i++) {
        for (int j = SIZE/2 - 1; j < SIZE; j++) {
            if (board[i][j] == 'o' && board[i+1][j-1] == 'o' && board[i+2][j-2] == 'o' && board[i+3][j-3] == 'o' &&
            board[i+4][j-4] == 'o') return LOST;
        }
    }


    return DRAW;

} // Decides about win or lose situations

void show_board(char board[SIZE][SIZE]) {

    printf("\n");
    printf("  %c | %c | %c | %c | %c | %c | %c | %c | %c | %c \n", board[0][0], board[0][1], board[0][2],
           board[0][3], board[0][4], board[0][5], board[0][6], board[0][7], board[0][8], board[0][9]);
    printf(" ---+---+---+---+---+---+---+---+---+---\n");
    printf("  %c | %c | %c | %c | %c | %c | %c | %c | %c | %c \n", board[1][0], board[1][1], board[1][2],
           board[1][3], board[1][4], board[1][5], board[1][6], board[1][7], board[1][8], board[1][9]);
    printf(" ---+---+---+---+---+---+---+---+---+---\n");
    printf("  %c | %c | %c | %c | %c | %c | %c | %c | %c | %c \n", board[2][0], board[2][1], board[2][2],
           board[2][3], board[2][4], board[2][5], board[2][6], board[2][7], board[2][8], board[2][9]);
    printf(" ---+---+---+---+---+---+---+---+---+---\n");
    printf("  %c | %c | %c | %c | %c | %c | %c | %c | %c | %c \n", board[3][0], board[3][1], board[3][2],
           board[3][3], board[3][4], board[3][5], board[3][6], board[3][7], board[3][8], board[3][9]);
    printf(" ---+---+---+---+---+---+---+---+---+---\n");
    printf("  %c | %c | %c | %c | %c | %c | %c | %c | %c | %c \n", board[4][0], board[4][1], board[4][2],
           board[4][3], board[4][4], board[4][5], board[4][6], board[4][7], board[4][8], board[4][9]);
    printf(" ---+---+---+---+---+---+---+---+---+---\n");
    printf("  %c | %c | %c | %c | %c | %c | %c | %c | %c | %c \n", board[5][0], board[5][1], board[5][2],
           board[5][3], board[5][4], board[5][5], board[5][6], board[5][7], board[5][8], board[5][9]);
    printf(" ---+---+---+---+---+---+---+---+---+---\n");
    printf("  %c | %c | %c | %c | %c | %c | %c | %c | %c | %c \n", board[6][0], board[6][1], board[6][2],
           board[6][3], board[6][4], board[6][5], board[6][6], board[6][7], board[6][8], board[6][9]);
    printf(" ---+---+---+---+---+---+---+---+---+---\n");
    printf("  %c | %c | %c | %c | %c | %c | %c | %c | %c | %c \n", board[7][0], board[7][1], board[7][2],
           board[7][3], board[7][4], board[7][5], board[7][6], board[7][7], board[7][8], board[7][9]);
    printf(" ---+---+---+---+---+---+---+---+---+---\n");
    printf("  %c | %c | %c | %c | %c | %c | %c | %c | %c | %c \n", board[8][0], board[8][1], board[8][2],
           board[8][3], board[8][4], board[8][5], board[8][6], board[8][7], board[8][8], board[8][9]);
    printf(" ---+---+---+---+---+---+---+---+---+---\n");
    printf("  %c | %c | %c | %c | %c | %c | %c | %c | %c | %c \n", board[9][0], board[9][1], board[9][2],
           board[9][3], board[9][4], board[9][5], board[9][6], board[9][7], board[9][8], board[9][9]);
    printf("\n");
} // Shows the game situation on the board

int minimax(char board[SIZE][SIZE], int depth, int ai_move, int *x, int *y) {

    int score, px, py, max_score, min_score, nx, ny;

    score = rate_situation(board);

    if (score == WIN || score == LOST || depth <= 0) return score;

    if (ai_move) {
        for (px = 0, max_score = 10 * LOST; px < SIZE; px++) {
            for (py = 0; py < SIZE; py++) {
                if (board[px][py] == ' ') {
                    board[px][py] = 'x';
                    score = minimax(board, depth - 1, FALSE, &nx, &ny);
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
                    score = minimax(board, depth - 1, TRUE, &nx, &ny);
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
}

int move_validation(char board[SIZE][SIZE], int x, int y) {

    if (x < 0 || x > 9 || y < 0 || y > 9) {
        return FALSE;
    }

    if (board[x][y] != ' ') {
        return FALSE;
    }

    return TRUE;
}
