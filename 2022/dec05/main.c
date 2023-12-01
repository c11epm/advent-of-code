#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *first = "HRBDZFLS";
char *second = "TBMZR";
char *third = "ZLCHNS";
char *forth = "SCFJ";
char *fifth = "PGHWRZB";
char *sixth = "VJZGDNMT";
char *seventh = "GLNWFSPQ";
char *eighth = "MZR";
char *ninth = "MCLGVRT";

void take_from_give_to(char *take_from, char *give_to) {
    int from_len = strlen(take_from);
    int to_len = strlen(give_to);

    give_to[to_len] = take_from[from_len - 1];
    take_from[from_len - 1] = '\0';
    give_to[to_len + 1] = '\0';
}

char *substr(char *input, int start, int length) {
    char *sub = malloc(length + 1);
    memcpy(sub, input + start, length);
    sub[length] = '\0';
    return sub;
}

void take_multiple_from_give_to(int number, char *from, char *to) {
    char *to_move = substr(from, strlen(from) - number, number);
    fprintf(stdout, "Move %d crates from %s makes substr %s\n", number, from, to_move);
    strcat(to, to_move);
    from[strlen(from)-number] = '\0';
    fprintf(stdout, "Move finished: %d crates from %s makes substr %s with results in: %s\n", number, from, to_move, to);
}

char *initiate_column(char *initial) {
    char *column = malloc(sizeof(char) * 60);
    strcpy(column, initial);
    return column;
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

    char **columns = malloc(sizeof(char *) * 9);
    columns[0] = initiate_column(first);
    columns[1] = initiate_column(second);
    columns[2] = initiate_column(third);
    columns[3] = initiate_column(forth);
    columns[4] = initiate_column(fifth);
    columns[5] = initiate_column(sixth);
    columns[6] = initiate_column(seventh);
    columns[7] = initiate_column(eighth);
    columns[8] = initiate_column(ninth);

    char **second_cols = malloc(sizeof(char *) * 9);
    second_cols[0] = initiate_column(first);
    second_cols[1] = initiate_column(second);
    second_cols[2] = initiate_column(third);
    second_cols[3] = initiate_column(forth);
    second_cols[4] = initiate_column(fifth);
    second_cols[5] = initiate_column(sixth);
    second_cols[6] = initiate_column(seventh);
    second_cols[7] = initiate_column(eighth);
    second_cols[8] = initiate_column(ninth);

    int move_blocks, from_column, to_column;
    while (fscanf(file, "move %d from %d to %d\n", &move_blocks, &from_column, &to_column) != -1) {
        //Part one
        for (int i = move_blocks; i > 0; i--) {
            take_from_give_to(columns[from_column - 1], columns[to_column - 1]);
        }
        //Part two
        take_multiple_from_give_to(move_blocks, second_cols[from_column - 1], second_cols[to_column - 1]);
    }
    for (int i = 0; i < 9; i++) {
        printf("%c", columns[i][strlen(columns[i]) - 1]);

        free(columns[i]);
    }
    printf("\n");
    for (int i = 0; i < 9; i++) {
        printf("%c", second_cols[i][strlen(second_cols[i]) - 1]);

        free(second_cols[i]);
    }
    free(columns);
    free(second_cols);
    printf("\n");
}