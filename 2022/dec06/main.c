#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char *substr(char *input, int start, int length) {
    char *sub = malloc(length + 1);
    memcpy(sub, input + start, length);
    sub[length] = '\0';
    return sub;
}

int recursive_unique(char* line, int index, int count) {
    int unique = 1;
    if(count == 1) {
        return 1;
    }
    char *sub = substr(line, index + 1, count);
    char *contains = strchr(sub, line[index]);
    if(contains != NULL) {
        unique = 0;
    }
    return recursive_unique(line, index + 1, count - 1) && unique;
}

int get_index_of_start_packet(char* input) {
    for(int i = 0; i < strlen(input) - 3; i++) {
        if(recursive_unique(input, i, 4)) {
            return i + 4;
        }
    }
    return 0;
}

int get_index_of_start_packet_second(char* input) {
    for(int i = 0; i < strlen(input) - 13; i++) {
        if(recursive_unique(input, i, 14)) {
            return i + 14;
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
    char input[4096];
    fscanf(file, "%s\n", input);

    int index = get_index_of_start_packet(input);
    int index_second = get_index_of_start_packet_second(input);
    fprintf(stdout, "%d\n", index);
    fprintf(stdout, "%d\n", index_second);
    fclose(file);
    return 0;
}
