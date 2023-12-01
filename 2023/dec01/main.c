#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int getDigit(char c) {
    return c - '0';
}

char *get_formatted_line(char *line, char *sub, int value) {
    char *result = strstr(line, sub);
    int position = result - line;
    int substringLength = strlen(line) - position;
    for(int i = 0; i < strlen(sub); i++) {
        line[position + i] = 'a';
    }
    line[position] = value + 48;
    return line;
}

int calculate_row(char *line) {

    int count = 0;
    int haveReadFirst = 0;
    int first = 0;
    int last = 0;
    while(line[count] != '\n') {
        if(isdigit(line[count])) {
            if(!haveReadFirst) {
                haveReadFirst = 1;
                first = getDigit(line[count]);
            }
            last = getDigit(line[count]);
        }
        count++;
    }
    fprintf(stdout, "score: %d %d = %d\n", first, last, first * 10 + last);
    return first * 10 + last;
}

int startsWith(const char *pre, const char *str)
{
    size_t lenpre = strlen(pre),
           lenstr = strlen(str);
    return lenstr < lenpre ? 0 : memcmp(pre, str, lenpre) == 0;
}

int resolve_digit_names(char *line) {
    char digits[9][5] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    //int digit_lengths[9] = {3, 4, 5, 4, 4, 3, 5, 5, 4};
    char *temp_line = line;


    for(int i = 0; i < 9; i++) {
        if(strstr(temp_line, digits[i])) {
            temp_line = get_formatted_line(temp_line, digits[i], i + 1);
            fprintf(stdout, "%d - %s\n", i, temp_line);
        }
    }
    return calculate_row(temp_line);
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

    char line[100];
    int score = 0;
    int score_two = 0;

    while(fgets(line, 100, file) != NULL) {
        //score += calculate_row(line);
        score_two += resolve_digit_names(line);
    }

    fprintf(stdout, "First: %d\n", score);
    fprintf(stdout, "Second: %d\n", score_two);

}

