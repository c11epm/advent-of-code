#include <stdio.h>
#include <stdlib.h>

void calculateThreeHighest(int *highest, int *highest2, int *highest3, int newValue) {
    if(newValue >= *highest) {
        *highest3 = *highest2;
        *highest2 = *highest;
        *highest = newValue;
    } else if(newValue >= *highest2) {
        *highest3 = *highest2;
        *highest2 = newValue;
    } else if(newValue >= *highest3) {
        *highest3 = newValue;
    }
}

int main(int argc, char** argv) {

    if(argc != 2) {
        fprintf(stderr, "Program takes two arguments\n");
        fprintf(stderr, "Usage: ./main <filename.txt>\n");
        return -1;
    }

    FILE *file;
    file = fopen(argv[1], "r");

    if(file == NULL) {
        fprintf(stderr, "Could not open file %s\n", argv[1]);
        return -1;
    }

    int max = 0;
    int elfValue = 0;
    char line[10];
    int highest =0;
    int highest2 = 0;
    int highest3 = 0;

    while(fgets(line, 10, file) != NULL) {
        int value = atoi(line);
        if(value == 0) {
            if(elfValue > max) {
                max = elfValue;
            }
            calculateThreeHighest(&highest, &highest2, &highest3, elfValue);
            elfValue = 0;
            //todo add three highest check
            continue;
        } else {
            elfValue += atoi(line);
        }
    }
    fprintf(stdout, "%d, %d, %d\n", highest, highest2, highest3);
    fprintf(stdout, "%d\n", max);
    fclose(file);
    return 0;
}
