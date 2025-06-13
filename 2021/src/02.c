#include <stdio.h>
#include <string.h>
#include "aoc.h"

void solve_02(char **lines, int line_count) {
    int horizontal = 0;
    int depth = 0;
    int new_depth = 0;

    for (int i = 0; i < line_count; i++) {
        char direction[10];
        int number;

        if (sscanf(lines[i], "%s %d", direction, &number) == 2) {
            if (strcmp(direction, "forward") == 0) {
                horizontal += number;
                new_depth += depth * number;
            }
            else if (strcmp(direction, "down") == 0) {
                depth += number;
            }
            else {
                depth -= number;
            }
        }
    }

    int part1 = horizontal * depth;
    int part2 = horizontal * new_depth;

    printf("Part 1: %d\nPart 2: %d\n", part1, part2);
}
