#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aoc.h"

void solve_08(char **lines, int line_count) {
    int part1 = 0, part2 = 0;

    for (int i = 0; i < line_count; i++) {
        char *outputs = strchr(lines[i], '|') + 2;

        char *token = strtok(outputs, " ");
        while (token) {
            int len = strlen(token);
            if (len == 2 || len == 3 || len == 4 || len == 7) {
                part1++;
            }
            token = strtok(NULL, " ");
        }
    }

    printf("Part 1: %d\nPart 2: %d\n", part1, part2);
}
