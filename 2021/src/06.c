#include "aoc.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static long memo[9][257] = {0};

long procreate(int timer, int days) {
    if (days <= 0)
        return 0;
    if (memo[timer][days])
        return memo[timer][days];

    long result = (timer == 0)
                      ? 1 + procreate(8, days - 1) + procreate(6, days - 1)
                      : procreate(timer - 1, days - 1);

    return memo[timer][days] = result;
}

void solve_06(char **lines, int line_count) {
    (void)line_count; // This shit is just to suppress the waring
    long part1 = 0, part2 = 0;

    char *token = strtok(lines[0], ",");
    while (token) {
        int num = atoi(token);
        part1 += 1 + procreate(num, 80);
        part2 += 1 + procreate(num, 256);
        token = strtok(NULL, ",");
    }

    printf("Part 1: %ld\nPart 2: %ld\n", part1, part2);
}
