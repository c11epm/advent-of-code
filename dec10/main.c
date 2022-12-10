#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CRT_ROWS 6
#define CRT_COLS 40

void check_signal_strength(int counter, int value, int *cycle_sum) {
    if ((counter - 20) % 40 == 0) {
        int add = (counter * value);
        *cycle_sum += add;
    }
}

int is_pixel_lit(int counter, int value) {
    return abs((counter % 40) - value) <= 1;
}

void update_sprite(char **image, int counter, int value) {
    int row = counter / 40;
    int col = counter % 40;
    int is_lit = is_pixel_lit(counter, value);
    //Some wierd stuff with last operation trying to access memory outside bounds
    if(counter < 240) image[row][col] = is_lit == 1 ? '#' : ' ';
}

int main(int argc, char **argv) {

    if (argc != 2) {
        fprintf(stderr, "Program takes two arguments\n");
        fprintf(stderr, "Usage: ./main <filename.txt>\n");
        return -1;
    }

    FILE *file;
    file = fopen(argv[1], "r");

    if (file == NULL) {
        fprintf(stderr, "Could not open file %s\n", argv[1]);
        return -1;
    }
    char line[30];
    int done_reading = 0;
    int prev_was_add_op = 0;
    int clock_counter = 0;
    int register_x = 1;
    int sum = 0;
    char **crt = malloc(sizeof(char *) * CRT_ROWS);

    for (int row = 0; row < CRT_ROWS; row++) {
        crt[row] = malloc(sizeof(char) * CRT_COLS);
        for (int col = 0; col < CRT_COLS; col++) {
            crt[row][col] = ' ';
        }
    }

    while (!done_reading) {
        if (prev_was_add_op) {
            int add;
            fscanf(file, "%d\n", &add);
            prev_was_add_op = 0;
            clock_counter++;
            check_signal_strength(clock_counter, register_x, &sum);
            register_x += add;
            update_sprite(crt, clock_counter, register_x);
            continue;
        }
        if (fscanf(file, "%s\n", line) != -1) {
            if (strcmp(line, "addx") == 0) {
                prev_was_add_op = 1;
                clock_counter++;
                check_signal_strength(clock_counter, register_x, &sum);
                update_sprite(crt, clock_counter, register_x);
                continue;
            } else if (strcmp(line, "noop") == 0) {
                prev_was_add_op = 0;
                clock_counter++;
                check_signal_strength(clock_counter, register_x, &sum);
                update_sprite(crt, clock_counter, register_x);
            } else {
                printf("Not recognized command: %s\n", line);
            }
        } else {
            done_reading = 1;
        }
    }

    printf("%d\n", sum);
    for (int row = 0; row < CRT_ROWS; row++) {
        for (int col = 0; col < CRT_COLS; col++) {
            printf("%c",crt[row][col]);
        }
        printf("\n");
    }

    fclose(file);
    return 0;
}