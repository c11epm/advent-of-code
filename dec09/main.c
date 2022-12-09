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
    while (fscanf(file, "%c %d\n", &dir, &steps) != -1) {

    }

    rope *r = malloc(sizeof(rope));
    r->head = malloc(sizeof(end));
    r->tail = malloc((sizeof(end)));
    r->head->x = 5;
    r->head->y = 0;

    r->tail->x = 0;
    r->tail->y = 0;

    printf("%d\n", r->head->x);

    fclose(file);
    return 0;
}