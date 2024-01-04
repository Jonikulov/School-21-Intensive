#include <stdio.h>

#define FIELD_WIDTH 80
#define FIELD_HEIGHT 25
#define RACKET_SIZE 3
#define BALL_SIZE 1

int racket1_pos = FIELD_HEIGHT / 2;
int racket2_pos = FIELD_HEIGHT / 2;
int ball_pos_x = FIELD_WIDTH / 2;
int ball_pos_y = FIELD_HEIGHT / 2;
int ball_dir_x = -1;
int ball_dir_y = -1;
int score_player1 = 0;
int score_player2 = 0;

void display() {
    printf("\e[1;1H\e[2J");  // Clear screen

    // Display field
    for (int i = 0; i < FIELD_HEIGHT; i++) {
        for (int j = 0; j < FIELD_WIDTH; j++) {
            if ((j == 0 || j == FIELD_WIDTH - 1) && i != 0 && i != FIELD_HEIGHT - 1) {
                printf("|");  // Vertical borders
            } else if (i == 0 || i == FIELD_HEIGHT - 1) {
                printf("-");  // Horizontal borders
            } else if (j == ball_pos_x && i == ball_pos_y) {
                printf("O");  // Ball
            } else if (j == 1 && (i == racket1_pos || i == racket1_pos + 1 || i == racket1_pos + 2)) {
                printf("A");  // Player 1 racket
            } else if (j == FIELD_WIDTH - 2 &&
                       (i == racket2_pos || i == racket2_pos + 1 || i == racket2_pos + 2)) {
                printf("B");  // Player 2 racket
            } else {
                printf(" ");  // Empty space
            }
        }
        printf("\n");
    }

    // Display score
    printf("\t\tScore: Player A -  %d | %d  - Player B\n", score_player1, score_player2);
}

void update() {
    // Move ball
    ball_pos_x += ball_dir_x;
    ball_pos_y += ball_dir_y;

    // Ball collision with top and bottom walls
    if (ball_pos_y == 0 || ball_pos_y == FIELD_HEIGHT - 1) {
        ball_dir_y = -ball_dir_y;
    }

    // Ball collision with rackets
    if ((ball_pos_x == 1 && ball_pos_y >= racket1_pos && ball_pos_y < racket1_pos + RACKET_SIZE) ||
        (ball_pos_x == FIELD_WIDTH - 2 && ball_pos_y >= racket2_pos &&
         ball_pos_y < racket2_pos + RACKET_SIZE)) {
        ball_dir_x = -ball_dir_x;
    }

    // Ball out of bounds (score)
    if (ball_pos_x == 0 || ball_pos_x == FIELD_WIDTH - 1) {
        if (ball_pos_x == 0) {
            score_player2++;
        } else {
            score_player1++;
        }

        // Reset ball position
        ball_pos_x = FIELD_WIDTH / 2;
        ball_pos_y = FIELD_HEIGHT / 2;
    }

    // Racket movement
    char input = getchar();
    if (input == 'a' && racket1_pos > 1) {
        racket1_pos--;
    } else if (input == 'z' && racket1_pos < FIELD_HEIGHT - RACKET_SIZE - 1) {
        racket1_pos++;
    } else if (input == 'k' && racket2_pos > 1) {
        racket2_pos--;
    } else if (input == 'm' && racket2_pos < FIELD_HEIGHT - RACKET_SIZE - 1) {
        racket2_pos++;
    } else if (input == ' ') {
        // Space bar to skip action
    }
}

int main() {
    while (score_player1 < 21 && score_player2 < 21) {
        display();
        update();
    }

    // Display winner
    display();
    if (score_player1 == 21) {
        printf("\nCongratulations! Player A wins!\n");
    } else {
        printf("\nCongratulations! Player B wins!\n");
    }

    return 0;
}