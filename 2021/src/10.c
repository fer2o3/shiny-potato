#include <stdio.h>
#include <stdlib.h>
#include "aoc.h"

long check_line(char *line) {
    char stack[200];
    int top = -1;

    for (int i = 0; line[i]; i++) {
        char c = line[i];

        if (c == '(' || c == '[' || c == '{' || c == '<') {
            stack[++top] = c;
        } else {
            if (top == -1 || 
                (c == ')' && stack[top] != '(') ||
                (c == ']' && stack[top] != '[') ||
                (c == '}' && stack[top] != '{') ||
                (c == '>' && stack[top] != '<')) {

                return (c == ')') ? 3 : (c == ']') ? 57 : (c == '}') ? 1197 : 25137;
            }
            top--;
        }
    }

    long score = 0;
    for (int i = top; i >= 0; i--) {
        score = score * 5 + ((stack[i] == '(') ? 1 : (stack[i] == '[') ? 2 : 
                            (stack[i] == '{') ? 3 : 4);
    }
    return -score;
}

int compare(const void *a, const void *b) {
    return (*(long*)a > *(long*)b) - (*(long*)a < *(long*)b);
}

void solve_10(char **lines, int line_count) {
    long part1 = 0, arr[200];
    int len = 0;

    for (int i = 0; i < line_count; i++) {
        long score = check_line(lines[i]);
        if (score > 0) part1 += score;
        else arr[len++] = -score;
    }

    qsort(arr, len, sizeof(long), compare);

    printf("Part 1: %ld\nPart 2: %ld\n", part1, arr[len/2]);
}
