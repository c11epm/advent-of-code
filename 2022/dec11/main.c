#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef void *data;

typedef long long (*func)(long long , long long );

typedef struct elem {
    data data;
    struct elem *next;
} li_list;

typedef struct monkey {
    li_list *items;
    func operation;
    int *operation_value;
    func test;
    int *test_value;
    int *is_true;
    int *is_false;
    int *no_of_inspects;
} monkey;

li_list *create_item(data data) {
    li_list *item = (li_list *) malloc(sizeof(li_list));
    item->data = data;
    item->next = NULL;

    return item;
}

long long f_add(long long a, long long b) {
    //printf("Add operation with %d + %d\n", a, b);
    return a + b;
}

long long f_sub(long long a, long long b) {
    return a - b;
}

long long f_mul(long long a, long long b) {
    if (b == -1) {
        return a * a;
    }
    return a * b;
}

long long f_is_divisible(long long a, long long b) {
    return (a % b == 0);
}

char *substr(char *input, int start, int length) {
    char *sub = malloc(length + 1);
    memcpy(sub, input + start, length);
    sub[length] = '\0';
    return sub;
}

void print_monkey_list(li_list *monkeys) {
    li_list *element = monkeys;
    while (element != NULL) {
        element = element->next;
    }
}

//TODO Cheat with substring?

monkey *get_monkey_data(FILE *file) {
    monkey *monkey1 = (monkey *) malloc(sizeof(monkey));
    li_list *head = (li_list *) malloc(sizeof(li_list));
    li_list *items;
    char line[60];
    if (fgets(line, 60, file) != NULL) {
        //Starting
        int d_index = 0;
        line[strlen(line) - 1] = '\0';

        char *tok;
        char *sub = substr(line, 18, strlen(line) - 18);
        tok = strtok(sub, ", ");
        while (tok != NULL) {

            long long *val = (long long *) malloc(sizeof(long long));
            *val = atoi(tok);
            printf("%lld ", *val);
            tok = strtok(NULL, ", ");

            if (d_index > 0) {
                items->next = create_item(val);
                items = items->next;
            } else {
                head = create_item(val);
                items = head;
            }
            d_index++;
        }
        monkey1->items = head;
        printf("\n");
    }
    if (fgets(line, 60, file) != NULL) {
        line[strlen(line) - 1] = '\0';
        char *sub = substr(line, 23, strlen(line) - 23);
        if (strstr(sub, "*")) {
            if (strstr(sub, "old")) {
                //old * old
                monkey1->operation = f_mul;
                int *op_value = (int *) malloc(sizeof(int));
                *op_value = -1;
                monkey1->operation_value = op_value;
            } else {
                int *op_value = (int *) malloc(sizeof(int));
                char op;
                sscanf(sub, "%c %d\n", &op, op_value);
                monkey1->operation = f_mul;
                monkey1->operation_value = op_value;
            }
        } else {

            char op;
            int *op_value = (int *) malloc(sizeof(int));
            sscanf(sub, "%c %d\n", &op, op_value);
            printf("Operation: new = old %c %d\n", op, *op_value);

            if (op == '+') {
                monkey1->operation = f_add;
                monkey1->operation_value = op_value;
            }
        }
        fprintf(stdout, "Operarion %s\n", sub);
    }
    if (fgets(line, 60, file) != NULL) {
        //Test
        line[strlen(line) - 1] = '\0';
        char *sub = substr(line, 21, strlen(line) - 21);
        monkey1->test = f_is_divisible;
        int *test_value = (int *) malloc(sizeof(int));
        *test_value = atoi(sub);
        monkey1->test_value = test_value;
        fprintf(stdout, "Test: divisible by %d\n", *monkey1->test_value);
    }
    if (fgets(line, 60, file) != NULL) {
        //True
        line[strlen(line) - 1] = '\0';
        char *sub = substr(line, 29, strlen(line) - 29);
        int *true = (int *) malloc(sizeof(int));
        *true = atoi(sub);
        monkey1->is_true = true;
        fprintf(stdout, "True %d\n", *monkey1->is_true);
    }
    if (fgets(line, 60, file) != NULL) {
        //False
        char *sub = substr(line, 30, strlen(line) - 30);
        int *false = (int *) malloc(sizeof(int));
        *false = atoi(sub);
        monkey1->is_false = false;
        fprintf(stdout, "False %d\n", *monkey1->is_false);
    }
    if (fgets(line, 60, file) != NULL) {
        //False
        line[strlen(line) - 1] = '\0';
    }
    int *insp = (int *) malloc(sizeof(int));
    *insp = 0;
    monkey1->no_of_inspects = insp;
    return monkey1;
}

void process_monkey(monkey *monkey_to_process, monkey **monkeys, int use_div_three_worry_level) {
    while (monkey_to_process->items != NULL) {
        long long value = *(long long *) monkey_to_process->items->data;
        long long new = monkey_to_process->operation(value, *monkey_to_process->operation_value);
        if (use_div_three_worry_level == 1) {
            new = new / 3;
        } else {
            //The product of all primes in the divisible input rows
            //2 * 3 * 5 * 7 * 11 * 13 * 17 * 19
            new %= 9699690;
        }
        long long *i = (long long *) malloc(sizeof(long long));
        *i = new;
        li_list *new_item = create_item(i);
        monkey *throw_to;

        if (monkey_to_process->test(new, *monkey_to_process->test_value)) {
            throw_to = monkeys[*monkey_to_process->is_true];
        } else {
            throw_to = monkeys[*monkey_to_process->is_false];
        }

        new_item->next = throw_to->items;
        throw_to->items = new_item;
        *(monkey_to_process->no_of_inspects) = (*monkey_to_process->no_of_inspects) + 1;
        //Pops monkeys item aswell
        monkey_to_process->items = monkey_to_process->items->next;
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

    int monkey_index;
    monkey **monkeys = malloc(sizeof(monkey *) * 8);
    char line[60];
    while (fgets(line, 60, file) != NULL) {
        sscanf(line, "Monkey %d:", &monkey_index);
        fprintf(stdout, "Monkey index: %d\n", monkey_index);
        monkeys[monkey_index] = get_monkey_data(file);
    }
    printf("\n\n");

    printf("%d\n", *(int *) monkeys[0]->items->data);

    //Change values 20 for p1 10000 for p2
    for (int i = 0; i < 10000; i++) {
        for (int j = 0; j < 8; j++) {
            //Process monkey
            //Change value 1 for p1, 0 for p2
            process_monkey(monkeys[j], monkeys, 0);
            //go to next monkey
        }
    }

    int index = 0;
    int highest = 0;
    int second_highest = 0;
    for (int j = 0; j < 8; j++) {
        int monkey_inspect = *(int *) monkeys[j]->no_of_inspects;
        if(monkey_inspect > highest) {
            second_highest = highest;
            highest = monkey_inspect;
        } else if(monkey_inspect > second_highest) {
            second_highest = monkey_inspect;
        }
        printf("Monkey %d inspected items %d times.\n", index, monkey_inspect);
    }
    fprintf(stdout, "%lld\n", (long long)highest * second_highest);
    //fscanf(file, "%d\n", &add);



    fclose(file);
    return 0;
}