#include <stdio.h>
#include <stdlib.h>

typedef struct end {
    int x;
    int y;
} end;

typedef struct rope {
    end *head;
    end *tail;
} rope;

void move_head_direction(end *head, char dir) {
    switch (dir) {
        case 'R':
            head->x = head->x + 1;
            break;
        case 'U':
            head->y = head->y + 1;
            break;
        case 'D':
            head->y = head->y - 1;
            break;
        case 'L':
            head->x = head->x - 1;
            break;
        default:
            break;
    }
}

void move_tail(end *tail, end *head, int **visited) {
    if(abs(tail->x - head->x) > 1) {
        if(tail->y == head->y) {
            tail->x = tail->x + (head->x > tail->x ? 1 : -1);
        }
        else {
            tail->y = tail->y + (head->y > tail->y ? 1 : -1);
            tail->x = tail->x + (head->x > tail->x ? 1 : -1);
        }

        printf("head at: %d %d, tail moved to: %d %d\n",head->x, head->y, tail->x, tail->y);
        if(visited != NULL) visited[tail->y][tail->x] = 1;
    }
     else if(abs(tail->y - head->y) > 1) {
        if(tail->x == head->x) {
            tail->y = tail->y + (head->y > tail->y ? 1 : -1);
        }
        else {
            tail->y = tail->y + (head->y > tail->y ? 1 : -1);
            tail->x = tail->x + (head->x > tail->x ? 1 : -1);
        }
        printf("head at: %d %d, tail moved to: %d %d\n",head->x, head->y, tail->x, tail->y);
        if(visited != NULL) visited[tail->y][tail->x] = 1;
    }
}

void move_second_rope(end **second, char dir, int **tail_visited) {
    move_head_direction(second[0], dir);
    for(int i = 1; i < 9; i++) {
        move_tail(second[i], second[i-1], NULL);
    }
    move_tail(second[9], second[8], tail_visited);
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
    char dir;
    int steps;
    int **tail_visited = malloc(sizeof(int *) * 1000);
    int **second_tail_visited = malloc(sizeof(int *) * 1000);
    for (int i = 0; i < 1000; i++) {
        tail_visited[i] = malloc(sizeof(int) * 1000);
        second_tail_visited[i] = malloc(sizeof(int) * 1000);
        for(int j = 0; j < 1000; j++) {
            tail_visited[i][j] = 0;
            second_tail_visited[i][j] = 0;
        }
    }
    rope *r = malloc(sizeof(rope));
    r->head = malloc(sizeof(end));
    r->tail = malloc(sizeof(end));
    r->head->x = 500;
    r->head->y = 500;

    r->tail->x = 500;
    r->tail->y = 500;

    end **second_rope = malloc(sizeof(end *) * 10);
    for(int i = 0; i < 10; i++) {
        second_rope[i] = malloc(sizeof(end));
        second_rope[i]->x = 500;
        second_rope[i]->y = 500;
    }
    while (fscanf(file, "%c %d\n", &dir, &steps) != -1) {
        for (int i = 0; i < steps; i++) {
            move_head_direction(r->head, dir);
            move_tail(r->tail, r->head, tail_visited);
            move_second_rope(second_rope, dir, second_tail_visited);
        }
    }
    tail_visited[500][500] = 1;
    second_tail_visited[500][500] = 1;
    int visited = 0;
    int second_visited = 0;
    for(int y = 0; y < 1000; y++){
        for(int x = 0; x <1000; x++) {
            visited += tail_visited[y][x];
            second_visited += second_tail_visited[y][x];
        }
    }

    printf("%d\n", visited);
    printf("%d\n", second_visited);

    fclose(file);
    return 0;
}