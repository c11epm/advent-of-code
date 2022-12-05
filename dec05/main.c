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

void take_from_give_to(char* take_from, char* give_to) {
    int from_len = strlen(take_from);
    int to_len = strlen(give_to);

    give_to[to_len] = take_from[from_len - 1];
    take_from[from_len - 1] = '\0';
    give_to[to_len + 1] = '\0';
}

char *initiate_column(char* initial) {
    char* column = malloc(sizeof(char) * 60);
    strcpy(column, initial);
    return column;
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

    char** columns = malloc(sizeof (char*)*9);
    columns[0] = initiate_column(first);
    columns[1] = initiate_column(second);
    columns[2] = initiate_column(third);
    columns[3] = initiate_column(forth);
    columns[4] = initiate_column(fifth);
    columns[5] = initiate_column(sixth);
    columns[6] = initiate_column(seventh);
    columns[7] = initiate_column(eighth);
    columns[8] = initiate_column(ninth);

    int move_blocks, from_column, to_column;
    while(fscanf(file, "move %d from %d to %d\n", &move_blocks, &from_column, &to_column) != -1) {
        //fprintf(stdout, "move %d from %d to %d\n", move_blocks, from_column, to_column);
        for(int i = move_blocks; i > 0; i--) {
            take_from_give_to(columns[from_column - 1], columns[to_column - 1]);
        }
    }
    for(int i = 0; i < 9; i++) {
        printf("%c", columns[i][strlen(columns[i])- 1]);
    }
    printf("\n");
}