#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WIDTH 64
#define ROWS 41
#define PATH 8
#define TRIED 2

typedef struct coordinate {
    int x;
    int y;
} coordinate;

int char_to_height(char a) {
    return ((int) (a)) - 96;
}

int is_walkable(int from, int to) {
    //Is allowed to move to place where value is one higher! And go to lower!
    return (to - from) <= 1;
}

int is_walkable_p2(int from, int to) {
    return (to - from) >= -1;
}

int is_visited(int **path, int x, int y) {
    return path[y][x];
}

void print_matrix(int matrix[ROWS][WIDTH]) {
    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < WIDTH; c++) {
            printf("%3d ", matrix[r][c]);
        }
        printf("\n");
    }
}

void print_matrix_pointer(int **matrix) {
    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < WIDTH; c++) {
            printf("%3d ", matrix[r][c]);
        }
        printf("\n");
    }
}

int is_valid_position(int x, int y, int **path, int step) {
    if(x < 0 || x >= WIDTH) {
        printf("X out of bounds\n");
        return 0;
    }
    if(y < 0 || y >= ROWS) {
        printf("y out of bounds\n");
        return 0;
    }
    return  1;
}

//Check if next position is possible to move to
//TODO Maybe some sort of no_of_steps_param?
int traverse(int x, int y, coordinate *end, int map[ROWS][WIDTH], int **path, int step) {
    if (!is_valid_position(x, y, path, step)) {
        return 0;
    }
    if (map[y][x] == 1) {
        printf("Goal!\n");
        path[y][x] = step;
        //return 1;
    }
    if(path[y][x] > step) {
        path[y][x] = step;
    }else {
        return 0;
    }

    //North
    if (is_walkable_p2(map[y][x], map[y - 1][x]) && traverse(x, y - 1, end, map, path, step+1)) {
        path[y][x] = step;
        return 1;
    }
    //West
    if (is_walkable_p2(map[y][x], map[y][x - 1]) && traverse(x - 1, y, end, map, path, step+1)) {
        path[y][x] = step;
        return 1;
    }
    //South
    if (is_walkable_p2(map[y][x], map[y + 1][x]) && traverse(x, y + 1, end, map, path, step+1)) {
        path[y][x] = step;
        return 1;
    }
    //East
    if (is_walkable_p2(map[y][x], map[y][x + 1]) && traverse(x + 1, y, end, map, path, step+1)) {
        path[y][x] = step;
        return 1;
    }

    //print_matrix_pointer(path);
    //printf("\n");
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
    int **path = malloc(sizeof(int *) * ROWS);
    coordinate start;
    coordinate end;
    int row = 0;
    char line[64];
    while (fscanf(file, "%s\n", line) != -1) {
        path[row] = malloc(sizeof(int) * WIDTH);
        for (int i = 0; i < strlen(line); i++) {
            path[row][i] = 999;
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
        //printf("%s\n", line);
    }

    traverse(end.x, end.y, &start, height_matrix, path, 0);
    //BFS(start.x, start.y, &end, height_matrix, path);
    print_matrix_pointer(path);
    int low = 999;
    for(int r = 0; r < ROWS; r++) {
        for(int c = 0; c < WIDTH; c++) {
            if(height_matrix[r][c] < low && path[r][c] == 1) {
                low = height_matrix[r][c];
            }
        }
    }
    printf("%d\n", low);
    printf("\n\n");
    print_matrix(height_matrix);
    printf("%d", path[end.y][end.y]);
    fclose(file);
    return 0;
}