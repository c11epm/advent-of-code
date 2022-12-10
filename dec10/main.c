#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void check_signal_strength(int counter, int value, int *cycle_sum) {
    printf("Counter: %d\n", counter );
    if ((counter - 20) % 40 == 0) {
        int add = (counter * value);
        *cycle_sum += add;
    }
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

    while (!done_reading) {
        if (prev_was_add_op) {
            int add;
            fscanf(file, "%d\n", &add);
            prev_was_add_op = 0;
            clock_counter++;
            check_signal_strength(clock_counter, register_x, &sum);
            register_x += add;
            continue;
        }
        if (fscanf(file, "%s\n", line) != -1) {
            if (strcmp(line, "addx") == 0) {
                prev_was_add_op = 1;
                clock_counter++;
                check_signal_strength(clock_counter, register_x, &sum);
                continue;
            }
            else if (strcmp(line, "noop") == 0) {
                prev_was_add_op = 0;
                clock_counter++;
                check_signal_strength(clock_counter, register_x, &sum);
            } else {
                printf("Not recognized command: %s\n", line);
            }
        } else {
            done_reading = 1;
        }
    }

    printf("%d\n", sum);


    fclose(file);
    return 0;
}