#include <ncurses.h>
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
    clear();  // Clear screen in ncurses

    // Display field
    for (int i = 0; i < FIELD_HEIGHT; i++) {
        for (int j = 0; j < FIELD_WIDTH; j++) {
            if ((j == 0 || j == FIELD_WIDTH - 1) && i != 0 && i != FIELD_HEIGHT - 1) {
                mvprintw(i, j, "|");  // Vertical borders
            } else if (i == 0 || i == FIELD_HEIGHT - 1) {
                mvprintw(i, j, "-");  // Horizontal borders
            } else if (j == ball_pos_x && i == ball_pos_y) {
                mvprintw(i, j, "O");  // Ball
            } else if (j == 1 && (i == racket1_pos || i == racket1_pos + 1 || i == racket1_pos + 2)) {
                mvprintw(i, j, "A");  // Player 1 racket
            } else if (j == FIELD_WIDTH - 2 &&
                       (i == racket2_pos || i == racket2_pos + 1 || i == racket2_pos + 2)) {
                mvprintw(i, j, "B");  // Player 2 racket
            }
        }
    }

    // Display score
    mvprintw(FIELD_HEIGHT + 1, 0, "Score: Player A -  %d | %d  - Player B", score_player1, score_player2);

    // Refresh the screen
    refresh();
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
    int input = getch();
    switch (input) {
        case 'a':
            if (racket1_pos > 1) {
                racket1_pos--;
            }
            break;
        case 'z':
            if (racket1_pos < FIELD_HEIGHT - RACKET_SIZE - 1) {
                racket1_pos++;
            }
            break;
        case 'k':
            if (racket2_pos > 1) {
                racket2_pos--;
            }
            break;
        case 'm':
            if (racket2_pos < FIELD_HEIGHT - RACKET_SIZE - 1) {
                racket2_pos++;
            }
            break;
        case ' ':
            // Space bar to skip action
            break;
    }
}

int main() {
    // Initialize ncurses
    initscr();
    keypad(stdscr, TRUE);  // Enable special keys
    timeout(100);          // Set input timeout to 100 milliseconds

    while (score_player1 < 21 && score_player2 < 21) {
        display();
        update();
    }

    // Display winner
    display();
    if (score_player1 == 21) {
        printw("\nCongratulations! Player A wins!\n");
    } else {
        printw("\nCongratulations! Player B wins!\n");
    }

    // Cleanup ncurses
    endwin();

    return 0;
}