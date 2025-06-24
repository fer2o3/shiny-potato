#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aoc.h"

long get_score(char c) {
    switch (c) {
        case ')': return 3;
        case ']': return 57;
        case '}': return 1197;
        case '>': return 25137;
        default: return 0;
    }
}

long get_value(char c) {
    switch (c) {
        case '(': return 1;
        case '[': return 2;
        case '{': return 3;
        case '<': return 4;
        default: return 0;
    }
}

char match_char(char c) {
    switch (c) {
        case '(': return ')';
        case '[': return ']';
        case '{': return '}';
        case '<': return '>';
        default: return 0;
    }
}

long check_line(char *line) {
    char stack[200];
    long top = -1;

    for (long i = 0; line[i]; i++) {
        char c = line[i];

        if (c == '(' || c == '[' || c == '{' || c == '<') {
            stack[++top] = c;
        }

        else if (c == ')' || c == ']' || c == '}' || c == '>') {
            if (top == -1) {
                return get_score(c);
            }

            char expected = match_char(stack[top]);
            if (c != expected) {
                return get_score(c);
            }

            top--;
        }
    }

    long score = 0;
    for (long i = top; i >= 0; i--) {
        score *= 5;
        score += get_value(stack[i]);
    }

    return -score;
}

void sort(long *arr, long len) {
    for (long i = 1; i < len; ++i) {
        long key = arr[i], j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void solve_10(char **lines, int line_count) {
    long part1 = 0, part2 = 0;
    long arr[200];
    long len = 0;

    for (long i = 0; i < line_count; i++) {
        long score = check_line(lines[i]);
        if (score >= 0) part1 += score;
        else arr[len++] = -score;
    }
    
    sort(arr, len);
    part2 = arr[len/2];

    printf("Part 1: %ld\nPart 2: %ld\n", part1, part2);
}
