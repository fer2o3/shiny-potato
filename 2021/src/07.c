#include "aoc.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int abs_diff(int a, int b) { return a > b ? a - b : b - a; }

int triangular(int n) { return n * (n + 1) / 2; }

void solve_07(char **lines, int line_count) {
    (void)line_count; // This shit is just to suppress warning for now
    int positions[1000], count = 0, max_pos = 0;

    char *token = strtok(lines[0], ",");
    while (token) {
        positions[count] = atoi(token);
        if (positions[count] > max_pos)
            max_pos = positions[count];
        count++;
        token = strtok(NULL, ",");
    }

    int min1 = INT_MAX, min2 = INT_MAX;

    for (int target = 0; target <= max_pos; target++) {
        int cost1 = 0, cost2 = 0;
        for (int i = 0; i < count; i++) {
            int dist = abs_diff(target, positions[i]);
            cost1 += dist;
            cost2 += triangular(dist);
        }
        if (cost1 < min1)
            min1 = cost1;
        if (cost2 < min2)
            min2 = cost2;
    }

    printf("Part 1: %d\nPart 2: %d\n", min1, min2);
}
