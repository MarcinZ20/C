#include <stdio.h>

#define SIZE 3

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

    int x, y, score, counter = 0, depth = 9;
    char board[3][3] = {' ', ' ', ' ', ' ',' ',' ', ' ', ' ', ' '};

    while (1) {

        minimax(board, depth, TRUE, &x, &y);
        board[x][y] = 'x';
        show_board(board);
        counter++;
        score = rate_situation(board);

        if (score == WIN) {
            printf("You lost ... \n");
            return 1;
        } else if (score == LOST) {
            printf("You won ... impossible!\n");
            return -1;
        } else if (counter == 5) {
            printf("It's a draw - good job!\n");
            return 0;
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

        if (score == WIN || score == LOST) {
            printf("koniec"); 
            return 1;
        }
        depth -= 2;
    }
}

int rate_situation(char board[SIZE][SIZE])  {

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

    return DRAW;

} // Decides about win or lose situations

void show_board(char board[SIZE][SIZE]) {

    printf("\n");
    printf(" %c | %c | %c \n", board[0][0], board[0][1], board[0][2]);
    printf("---+---+---\n");
    printf(" %c | %c | %c \n", board[1][0], board[1][1], board[1][2]);
    printf("---+---+---\n");
    printf(" %c | %c | %c \n", board[2][0], board[2][1], board[2][2]);
    printf("\n");
    
} // Shows the current situation on the board

int minimax(char board[SIZE][SIZE], int depth, int ai_move, int *x, int *y) {

    int score, px, py, max_score, min_score, nx, ny;
    
    score = rate_situation(board);

    if (score == WIN || score == LOST || depth == 0) return score;

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
} // Calculates optimal move for the ai

int move_validation(char board[SIZE][SIZE], int x, int y) {
    
    if (x < 0 || x > 2 || y < 0 || y > 2) {
        return FALSE;
    }

    if (board[x][y] != ' ') {
        return FALSE;
    }

    return TRUE;
} // Validates humans move
