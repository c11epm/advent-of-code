#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WIDTH 64
#define ROWS 41
#define PATH 3
#define TRIED 2

typedef struct coordinate {
    int x;
    int y;
} coordinate;

int char_to_height(char a) {
    return ((int) (a)) - 96;
}

void dijkstra(int heights[ROWS][WIDTH], coordinate start) {

}

int is_walkable(int from, int to) {
    //Is allowed to move to place where value is one higher! And go to lower!
    return (from - to) >= -1;
}

void print_matrix(int matrix[ROWS][WIDTH]) {
    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < WIDTH; c++) {
            printf("%2d ", matrix[r][c]);
        }
        printf("\n");
    }
}

int is_valid_position(int x, int y, int path[ROWS][WIDTH]) {
    return x >= 0 && x < WIDTH && y >= 0 && y < ROWS && path[y][x] != TRIED;
}

//Check if next position is possible to move to
int traverse(int x, int y, coordinate end, int map[ROWS][WIDTH], int *path[ROWS][WIDTH]) {
    if (!is_valid_position(x, y)) {
        return 0;
    }
    if (x == end.x && y == end.y) {
        printf("Goal!");
        path[y][x] = PATH;
    } else {
        path[y][x] = TRIED;
    }

    //North
    if(traverse(x, y - 1, end, map, path)) {
        path[y - 1][x] = PATH;
        return 1;
    }
    //West
    if(traverse(x - 1, y, end, map, path)) {
        path[y][x - 1] = PATH;
        return 1;
    }
    //South
    if(traverse(x, y + 1, end, map, path)) {
        path[y + 1][x] = PATH;
        return 1;
    }
    //East
    if(traverse(x + 1, y, end, map, path)) {
        path[y][x + 1] = PATH;
        return 1;
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
    int height_matrix[ROWS][WIDTH];
    coordinate start;
    coordinate end;
    int row = 0;
    char line[64];
    while (fscanf(file, "%s\n", line) != -1) {
        for (int i = 0; i < strlen(line); i++) {
            if (line[i] == 'S') {
                start.x = i;
                start.y = row;
                height_matrix[row][i] = 1;
            } else if (line[i] == 'E') {
                end.x = i;
                end.y = row;
                height_matrix[row][i] = 26;
            } else {
                //printf("char %c, to val %d\n", line[i], char_to_height(line[i]));
                height_matrix[row][i] = char_to_height(line[i]);
            }
        }

        row++;
        printf("%s\n", line);
    }

    print_matrix(height_matrix);

    fclose(file);
    return 0;
}