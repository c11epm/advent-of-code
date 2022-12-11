#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef void *data;

typedef struct elem {
    data data;
    struct elem *next;
} li_list;

typedef struct monkey {
    li_list *items;
    char *operation;
    char *test;
    int is_true;
    int is_false;
} monkey;

li_list *create_item(data data) {
    li_list *item = (li_list *) malloc(sizeof(li_list));
    item->data = data;
    item->next = NULL;

    return item;
}

//TODO Cheat with substring?

monkey *get_monkey_data(FILE *file) {
    monkey *monkey1 = (monkey *) malloc(sizeof(monkey));
    monkey1->items = (li_list *) malloc(sizeof(li_list));
    char line[60];
    if (fgets(line, 60, file) != NULL) {
        //Starting
        line[strlen(line) - 1] = '\0';
        fprintf(stdout, "Starting %s\n", line);
    }
    if (fgets(line, 60, file) != NULL) {
        //Operation
        line[strlen(line) - 1] = '\0';
        fprintf(stdout, "Operarion %s\n", line);
    }
    if (fgets(line, 60, file) != NULL) {
        //Test
        line[strlen(line) - 1] = '\0';
        fprintf(stdout, "Test %s\n", line);
    }
    if (fgets(line, 60, file) != NULL) {
        //True
        line[strlen(line) - 1] = '\0';
        fprintf(stdout, "True %s\n", line);
    }
    if (fgets(line, 60, file) != NULL) {
        //False
        line[strlen(line) - 1] = '\0';
        fprintf(stdout, "False %s\n", line);
    }
    if (fgets(line, 60, file) != NULL) {
        //False
        line[strlen(line) - 1] = '\0';
        fprintf(stdout, "Empty %s\n", line);
    }
    return monkey1;
}

void read_monkey(FILE *file, li_list *monkey_list, int index) {
    li_list *item = monkey_list;

    for (int i = 1; i < index; i++) {
        if(item->next == NULL) {
            item->next = (li_list *) malloc(sizeof(li_list));
        }
        item = item->next;
    }
    item->data = get_monkey_data(file);
    item->next = NULL;
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

    int monkey_index;
    li_list *head_monkies = (li_list *) malloc(sizeof(li_list));
    char line[60];
    while (fgets(line, 60, file) != NULL) {
        fprintf(stdout, "Before sscanf\n");
        sscanf(line, "Monkey %d:", &monkey_index);
        fprintf(stdout, "Monkey index: %d\n", monkey_index);
        read_monkey(file, head_monkies, monkey_index);
    }
    //fscanf(file, "%d\n", &add);



    fclose(file);
    return 0;
}