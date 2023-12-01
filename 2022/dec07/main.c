#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int string_starts_with(char *str, char *starts_with) {
    return !strncmp(str, starts_with, strlen(starts_with));
}

void update_value_to_parent(int *parents, int *sizes, int parent, int value) {
    sizes[parent] += value;
    if(parent != 0) {
        update_value_to_parent(parents, sizes, parents[parent], value);
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
    int *parents = malloc(sizeof(int) * 1000);
    int *sizes = malloc(sizeof(int) * 1000);
    int current_folder = 0;
    int folder_index = 0;

    char line[100];
    while (fgets(line, 100, file) != NULL) {
        line[strlen(line) - 1] = '\0';
        if (string_starts_with(line, "$")) {
            if (!strcmp(line, "$ cd /")) {
                //This is first line, ignore
                continue;
            }
            if (strstr(line, "$ ls")) {
                continue;
            }
            if (strstr(line, "..")) {
                //TODO pop back to parent cd ..
                current_folder = parents[current_folder];
                continue;
            }
            //TODO increase folder pointer cd XXXXX command
            folder_index++;
            parents[folder_index] = current_folder;
            current_folder = folder_index;
        } else if (string_starts_with(line, "dir")) {
            continue;
        } else {
            char *size = strtok(line, " ");
            int s = atoi(size);
            sizes[current_folder] += s;
            update_value_to_parent(parents, sizes, parents[current_folder], s);
        }
    }
    int freeSpace = 70000000-sizes[0];
    int needed = 30000000-freeSpace;
    printf("%d\n", freeSpace);
    printf("%d\n", needed);
    int smallest = 99999999;
    long totalsum = 0;
    for(int i = 0; i < folder_index; i++) {
        if(sizes[i] < 100000) {
            totalsum += sizes[i];
        }
        if(sizes[i] > needed) {
            if(sizes[i] < smallest){
                smallest = sizes[i];
            }
        }
    }
    fprintf(stdout, "%ld\n", totalsum);
    fprintf(stdout, "%d\n", smallest);
    fclose(file);
    return 0;
}