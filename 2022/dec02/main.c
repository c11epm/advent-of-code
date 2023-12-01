#include <stdio.h>
#include <stdlib.h>

#define ROCK 1
#define PAPER 2
#define SCISSORS 3

#define WIN 1
#define TIE 0
#define LOSE -1

int get_points_from_abc_type(char opponent) {
    if(opponent == 'A') {
        return ROCK;
    } else if (opponent == 'B') {
        return PAPER;
    } else if (opponent == 'C') {
        return SCISSORS;
    } else {
        fprintf(stderr, "Type %c not recognized", opponent);
        return 0;
    }
}

int get_points_from_xyz_type(char me) {
        if(me == 'X') {
            return ROCK;
        } else if (me == 'Y') {
            return PAPER;
        } else if (me == 'Z') {
            return SCISSORS;
        } else {
            fprintf(stderr, "Type %c not recognized", me);
            return 0;
        }
}

int get_choise_points_from_opponent_and_win_status(char opponent, int win_status) {
    int value = (int) opponent - 'A';
    value = (value + win_status) % 3 + 1;
    fprintf(stderr, "Opponent choose: %c, win_status = %d, value = %d\n", opponent, win_status,value);
    if(value == 0) {
        value = 3;
    }
    return value;
}

int get_win_lose_status(char win_status) {
        if(win_status == 'X') {
            return LOSE;
        } else if (win_status == 'Y') {
            return TIE;
        } else if (win_status == 'Z') {
            return WIN;
        } else {
            fprintf(stderr, "Type %c not recognized", win_status);
            return -10;
        }
}

int is_tie(char opponent, char me) {
    if((opponent == 'A' && me == 'X') || (opponent == 'B' && me == 'Y') || (opponent == 'C' && me == 'Z')) {
        return 1;
    }
    return 0;
}

int calculate_winner(char opponent, char me) {
    if(is_tie(opponent, me)) {
        return 0;
    }
    if(opponent == 'A' && me == 'Y') {
        return 1;
    }
    if(opponent == 'B' && me == 'Z') {
        return 1;
    }
    if(opponent == 'C' && me == 'X') {
        return 1;
    }
    return -1;
}

void calculate_round(char opponent, char me, int *points_opponent, int *points_me) {
    *points_opponent += get_points_from_abc_type(opponent);
    *points_me += get_points_from_xyz_type(me);

    int winner = calculate_winner(opponent, me);
    if(winner == -1) {
    //fprintf(stdout, "Opponent wins: %c %c \n", opponent, me);
        *points_opponent += 6;
    } else if (winner == 1) {
    //fprintf(stdout, "Me wins: %c %c \n", opponent, me);
        *points_me += 6;
    } else {
    //fprintf(stdout, "Tie: %c %c \n", opponent, me);
        *points_opponent += 3;
        *points_me += 3;
    }
}

void calculate_round_second(char opponent, char win_status, int *points_opponent, int *points_me) {
    *points_opponent += get_points_from_abc_type(opponent);
    int winner = get_win_lose_status(win_status);
    *points_me += get_choise_points_from_opponent_and_win_status(opponent, winner);

    if(winner == -1) {
    fprintf(stdout, "Opponent wins: %c %c \n", opponent, win_status);
        *points_opponent += 6;
    } else if (winner == 1) {
    fprintf(stdout, "Me wins: %c %c \n", opponent, win_status);
        *points_me += 6;
    } else {
    fprintf(stdout, "Tie: %c %c \n", opponent, win_status);
        *points_opponent += 3;
        *points_me += 3;
    }

}


int main(int argc, char** argv) {

    if(argc != 2) {
        fprintf(stderr, "Program takes two arguments\n");
        fprintf(stderr, "Usage: ./main <filename.txt>\n");
        return -1;
    }

    FILE *file;
    file = fopen(argv[1], "r");

    if(file == NULL) {
        fprintf(stderr, "Could not open file %s\n", argv[1]);
        return -1;
    }

    char opponent;
    char me;
    int points_opponent = 0;
    int points_me = 0;
        int points_opponent_second = 0;
        int points_me_second = 0;

    while(fscanf(file, "%c %c\n", &opponent, &me) != -1) {
        //fprintf(stdout, "p1: %c, p2: %c\n", opponent, me);
        calculate_round(opponent, me, &points_opponent, &points_me);
        calculate_round_second(opponent, me, &points_opponent_second, &points_me_second);
    }

    fprintf(stdout, "Points: opponent: %d, me: %d\n", points_opponent, points_me);
    fprintf(stdout, "Points: opponent: %d, me: %d\n", points_opponent_second, points_me_second);
    fclose(file);
    return 0;
}
