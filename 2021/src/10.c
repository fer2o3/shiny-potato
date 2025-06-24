#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aoc.h"

int get_score(char illegal) {
    switch (illegal) {
        case ')': return 3;
        case ']': return 57;
        case '}': return 1197;
        case '>': return 25137;
        default: return 0;
    }
}

char match_char(char open) {
    switch (open) {
        case '(': return ')';
        case '[': return ']';
        case '{': return '}';
        case '<': return '>';
        default: return 0;
    }
}

int check_line(char *line) {
    char stack[200];
    int top = -1;
    
    for (int i = 0; line[i]; i++) {
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

    return 0;
}

void solve_10(char **lines, int line_count) {
    int part1 = 0, part2 = 0;

    for (int i = 0; i < line_count; i++) {
        int score = check_line(lines[i]);
        part1 += score;
    }

    printf("Part 1: %d\nPart 2: %d\n", part1, part2);
}
