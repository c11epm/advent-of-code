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

typedef struct list {
    end *pos;
    struct list *next;
} list;

int pos_equals(end *pos1, end *pos2) {
    return pos1->x == pos2->x && pos1->y == pos2->y;
}

int exists_in_list(list *l, end *pos) {
    do {
        if(pos_equals(l->pos, pos)) {
            return 1;
        }
    } while(l->next != NULL);
    return 0;
}

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
            tail->y = tail->y + (head->x > tail->x ? 1 : -1);
        }
        else {
            tail->y = tail->y + (head->y > tail->y ? 1 : -1);
            tail->x = tail->x + (head->x > tail->x ? 1 : -1);
        }

        printf("head at: %d %d, tail moved to: %d %d\n",head->x, head->y, tail->x, tail->y);

        visited[tail->y][tail->x] = 1;
    }
     else if(abs(tail->y - head->y) > 1) {
        if(tail->x == head->x) {
            tail->x = tail->x + (head->y > tail->y ? 1 : -1);
        }
        else {
            tail->y = tail->y + (head->y > tail->y ? 1 : -1);
            tail->x = tail->x + (head->x > tail->x ? 1 : -1);
        }
        printf("B %d %d\n", tail->x, tail->y);
        visited[tail->y][tail->x] = 1;
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
    char dir;
    int steps;
    int **tail_visited = malloc(sizeof(int *) * 1000);
    for (int i = 0; i < 1000; i++) {
        tail_visited[i] = malloc(sizeof(int) * 1000);
        for(int j = 0; j < 1000; j++) {
            tail_visited[i][j] = 0;
        }
    }
    rope *r = malloc(sizeof(rope));
    r->head = malloc(sizeof(end));
    r->tail = malloc(sizeof(end));
    r->head->x = 500;
    r->head->y = 500;

    r->tail->x = 500;
    r->tail->y = 500;
    while (fscanf(file, "%c %d\n", &dir, &steps) != -1) {
        for (int i = 0; i < steps; i++) {
            move_head_direction(r->head, dir);
            move_tail(r->tail, r->head, tail_visited);
        }
    }
    int visited = 0;
    for(int y = 0; y < 1000; y++){
        for(int x = 0; x <1000; x++) {
            visited += tail_visited[y][x];
        }
    }

    printf("%d\n", visited);

    fclose(file);
    return 0;
}