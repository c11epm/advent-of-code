#include <stdio.h>
#include <stdlib.h>

#define IS_IN_RANGE(number, low, high) (number >= low && number <=high)

int is_range_contained_by_other(int first_low, int first_high, int second_low, int second_high) {
    return (first_low >= second_low && first_high <= second_high) ||
           (second_low >= first_low && second_high <= first_high);
}

int is_ranges_overlapping_at_all(int first_low, int first_high, int second_low, int second_high) {
    return IS_IN_RANGE(first_low, second_low, second_high) ||
           IS_IN_RANGE(first_high, second_low, second_high) ||
           IS_IN_RANGE(second_low, first_low, first_high) ||
           IS_IN_RANGE(second_high, first_low, first_high);
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
    int a, b, c, d;
    int total_ranges_first = 0;
    int total_ranges_second = 0;
    while (fscanf(file, "%d-%d,%d-%d\n", &a, &b, &c, &d) != -1) {
        total_ranges_first += is_range_contained_by_other(a, b, c, d);
        total_ranges_second += is_ranges_overlapping_at_all(a, b, c, d);
    }

    fprintf(stdout, "%d\n", total_ranges_first);
    fprintf(stdout, "%d\n", total_ranges_second);
    return 0;
}