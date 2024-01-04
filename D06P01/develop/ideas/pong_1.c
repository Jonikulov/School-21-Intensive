#include <stdio.h>

void draw_board(int racket1_y, int racket2_y, int ball_pos_x, int ball_pos_y, int player_1, int player_2,
                int racket_size);

int main() {
    int ball_pos_x = 39;
    int ball_pos_y = 12;
    int racket1_y = 10;
    int racket2_y = 10;
    int balls_speed_x = 1;
    int balls_speed_y = 1;
    int player_1 = 0;
    int player_2 = 0;
    int racket_size = 3;

    do {
        printf("\033[2J\033[H");

        draw_board(racket1_y, racket2_y, ball_pos_x, ball_pos_y, player_1, player_2, racket_size);

        ball_pos_x += balls_speed_x;
        ball_pos_y += balls_speed_y;

        if (ball_pos_y <= 0 || ball_pos_y >= 22) {
            balls_speed_y *= -1;
        }

        if ((ball_pos_x == 1 && ball_pos_y >= racket1_y && ball_pos_y < racket1_y + 5) ||
            (ball_pos_x == 76 && ball_pos_y >= racket2_y && ball_pos_y < racket2_y + 5)) {
            balls_speed_x *= -1;
        }

        if (ball_pos_x < 0) {
            player_2++;
            ball_pos_x = 39;
            ball_pos_y = 12;
            balls_speed_x = 1;
            balls_speed_y = 1;
        } else if (ball_pos_x >= 78) {
            player_1++;
            ball_pos_x = 39;
            ball_pos_y = 12;
            balls_speed_x = -1;
            balls_speed_y = -1;
        }

        // Get pressed key id
        // A - 2560    Z - 2816    K - 5120    M - 5376
        const char *bashScript = "./get_pressed_key.sh";
        FILE *pipe = popen(bashScript, "r");
        int key_code = pclose(pipe);
        if (key_code == 2560) {
            if (racket1_y > 0) {
                racket1_y--;
            }
        } else if (key_code == 2816) {
            if (racket1_y < 23 - racket_size) {
                racket1_y++;
            }
        } else if (key_code == 5120) {
            if (racket2_y > 0) {
                racket2_y--;
            }
        } else if (key_code == 5376) {
            if (racket2_y < 23 - racket_size) {
                racket2_y++;
            }
        }
    } while (player_1 < 21 && player_2 < 21);

    printf("\n\nYour score: %d - %d", player_1, player_2);
    if (player_1 == 21) {
        printf("\nCongratulations to Player 1!\n\n");
    } else if (player_2 == 21) {
        printf("\nCongratulations to Player 2!\n\n");
    }

    return 0;
}

void draw_board(int racket1_y, int racket2_y, int ball_pos_x, int ball_pos_y, int player_1, int player_2,
                int racket_size) {
    int boards_width = 80;
    int boards_height = 25;

    printf("\t\t ___ ___ _  _  ___   ___  ___  _  _  ___ \n");
    printf("\t\t| _ \\_ _| \\| |/ __| | _ \\/ _ \\| \\| |/ __|\n");
    printf("\t\t|  _/| || .` | (_ | |  _/ (_) | .` | (_ |\n");
    printf("\t\t|_| |___|_|\\_|\\___| |_|  \\___/|_|\\_|\\___|\n");

    for (int j = 0; j < boards_width; j++) {
        printf("-");
    }

    printf("\n|");
    for (int i = 0; i < 24; i++) {
        printf(" ");
    }
    // Display game score
    printf("Player A -- %d  |  %d -- Player B", player_1, player_2);
    for (int i = 0; i < 23; i++) {
        printf(" ");
    }
    printf("|\n");

    for (int i = 0; i < boards_width; i++) {
        printf("=");
    }
    printf("\n");

    for (int i = 0; i < boards_height - 2; i++) {
        printf("{");
        for (int j = 0; j < boards_width - 2; j++) {
            if ((j == 1 && i >= racket1_y && i < racket1_y + racket_size) ||
                (j == 76 && i >= racket2_y && i < racket2_y + racket_size)) {
                printf("|");
            } else if (j == ball_pos_x && i == ball_pos_y) {
                printf("o");
            } else if (j == boards_width / 2 - 1) {
                printf("'");
            } else {
                printf(" ");
            }
        }
        printf("}\n");
    }

    for (int i = 0; i < boards_width; i++) {
        printf("=");
    }
    printf("\n");
}
