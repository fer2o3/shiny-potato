#include "aoc.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void solve_01(char **lines, int line_count) {
    int *input = malloc(line_count * sizeof(int));
    if (!input) {
        printf("Kachow ! Memory allocation failed\n");
        return;
    }

    for (int i = 0; i < line_count; i++) {
        input[i] = atoi(lines[i]);
    }

    int count = 0;
    for (int i = 1; i < line_count; i++) {
        if (input[i] > input[i - 1])
            count++;
    }
    int part1 = count;

    count = 0;
    for (int i = 3; i < line_count; i++) {
        int prev = input[i - 3] + input[i - 2] + input[i - 1];
        int cur = input[i - 2] + input[i - 1] + input[i];
        if (cur > prev)
            count++;
    }
    int part2 = count;

    printf("Part 1: %d\nPart 2: %d\n", part1, part2);

    free(input);
}
