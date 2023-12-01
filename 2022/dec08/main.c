#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WIDTH 100
#define LENGTH 100

int char_to_int(char c) {
    return ((int) (c)) - 48;
}

void initialize_seen(int **tree_seen) {
    for (int i = 0; i < WIDTH - 1; i++) {
        //left
        tree_seen[i][0] = 1;
        //top
        tree_seen[0][i] = 1;
        //right
        tree_seen[i][WIDTH - 2] = 1;
        //bot
        tree_seen[LENGTH - 2][i] = 1;
    }
}

void print(int **matrix) {
    for (int row = 0; row < LENGTH - 1; row++) {
        for (int col = 0; col < WIDTH - 1; col++) {
            printf("%d", matrix[row][col]);
        }
        printf("\n");
    }
}

int is_tree_seen(int **height, int row, int col) {
    int seen_top = 1;
    int seen_right = 1;
    int seen_left = 1;
    int seen_bot = 1;
    int tree_height = height[row][col];
    //top
    for (int i = row - 1; i >= 0; i--) {
        if (tree_height <= height[i][col]) {
            seen_top = 0;
            break;
        }
    }
    //right
    for (int i = col + 1; i < WIDTH - 1; i++) {
        if (tree_height <= height[row][i]) {
            seen_right = 0;
            break;
        }
    }
    //left
    for (int i = col - 1; i >= 0; i--) {
        if (tree_height <= height[row][i]) {
            seen_left = 0;
            break;
        }
    }
    //bot
    for (int i = row + 1; i < LENGTH - 1; i++) {
        if (tree_height <= height[i][col]) {
            seen_bot = 0;
            break;
        }
    }

    return seen_bot || seen_right || seen_top || seen_left;
}

void calculate_seen(int **seen, int **height) {
    for (int row = 1; row < LENGTH - 2; row++) {
        for (int col = 1; col < WIDTH - 2; col++) {
            seen[row][col] = is_tree_seen(height, row, col);
        }
    }
}

int sum_trees_seen(int **seen) {
    int seen_trees = 0;
    for (int row = 0; row < LENGTH - 1; row++) {
        for (int col = 0; col < WIDTH - 1; col++) {
            seen_trees += seen[row][col];
        }
    }
    return seen_trees;
}

int scenic_score_for_tree(int **height, int row, int col) {
    //Off by one, becuase, yeah!
    int seen_top = 1;
    int seen_right = 1;
    int seen_left = 1;
    int seen_bot = 1;
    int tree_height = height[row][col];
    //top
    for (int i = row - 1; i > 0; i--) {
        if (tree_height <= height[i][col]) {
            break;
        }
        seen_top++;
    }
    //right
    for (int i = col + 1; i < WIDTH - 2; i++) {
        if (tree_height <= height[row][i]) {
            break;
        }
        seen_right++;
    }
    //left
    for (int i = col - 1; i > 0; i--) {
        if (tree_height <= height[row][i]) {
            break;
        }
        seen_left++;
    }
    //bot
    for (int i = row + 1; i < LENGTH - 2; i++) {
        if (tree_height <= height[i][col]) {
            break;
        }
        seen_bot++;
    }
    printf("Scenic value for row %d col %d %d %d %d %d %d\n", row, col, seen_top, seen_right, seen_bot, seen_left,
           seen_bot * seen_right * seen_left * seen_top);
    return seen_bot * seen_right * seen_top * seen_left;
}

int highest_scenic_tree_value(int **height) {
    int scenic = 0;
    for (int row = 1; row < LENGTH - 2; row++) {
        for (int col = 1; col < WIDTH - 2; col++) {
            int scenic_tree = scenic_score_for_tree(height, row, col);
            if (scenic_tree > scenic) scenic = scenic_tree;
        }
    }
    return scenic;
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
    int **tree_seen = malloc(sizeof(int *) * LENGTH);
    int **tree_height = malloc(sizeof(int *) * LENGTH);

    char *line = malloc(sizeof(char) * (WIDTH + 1));
    int line_count = 0;
    while (fgets(line, WIDTH + 1, file) != NULL) {
        if (line[strlen(line) - 1] == '\n') line[strlen(line) - 1] = '\0';

        tree_height[line_count] = malloc(sizeof(int) * WIDTH);
        tree_seen[line_count] = malloc(sizeof(int) * WIDTH);
        for (int i = 0; i < strlen(line); i++) {
            tree_height[line_count][i] = char_to_int(line[i]);
            tree_seen[line_count][i] = 0;
        }
        line_count++;
    }

    initialize_seen(tree_seen);
    calculate_seen(tree_seen, tree_height);

    print(tree_height);
    printf("\n");
    print(tree_seen);

    printf("%d\n", sum_trees_seen(tree_seen));
    printf("%d\n", highest_scenic_tree_value(tree_height));

    fclose(file);

    return 0;
}