#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int is_duplicate_in_other_compartment(char character, char *other_compartment) {
    char input[2];
    input[0] = character;
    input[1] = '\0';
    char *ret = strstr(other_compartment, input);
    if (ret) {
        return 1;
    } else {
        return 0;
    }
}

int get_valuation_of_item(char item) {
    if (item >= 'a' && item <= 'z') {
        return (item - 'a') + 1;
    } else if (item >= 'A' && item <= 'Z') {
        return (item - 'A') + 27;
    } else {
        return 0;
    }
}

char *substr(char *input, int start, int length) {
    char *sub = malloc(length + 1);
    memcpy(sub, input + start, length);
    sub[length] = '\0';
    return sub;
}

int calculate_duplicate_values(char *line) {

    int length = strlen(line);
    if (length % 2 != 0) {
        fprintf(stderr, "Line not even length, line: %s, length: %d\n", line, length);
    }

    int half = length / 2;
    char *second_half = substr(line, half, half);

    for (int i = 0; i < half; i++) {
        if (is_duplicate_in_other_compartment(line[i], second_half)) {
            return get_valuation_of_item(line[i]);
        }
    }
    return 0;
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
    int total_value = 0;
    char line[60];
    while (fscanf(file, "%s\n", line) != -1) {
        total_value += calculate_duplicate_values(line);
    }
    fprintf(stdout, "%d\n", total_value);
    return 0;
}