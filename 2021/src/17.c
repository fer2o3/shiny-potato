#include "aoc.h"
#include <limits.h>
#include <stdio.h>

void solve_17(char **lines, int line_count) {
    (void)line_count; // This shit is just to suppress warning for now
    int min_x, max_x, min_y, max_y;
    sscanf(lines[0], "target area: x=%d..%d, y=%d..%d", &min_x, &max_x, &min_y,
           &max_y);

    int part2 = 0;
    int max_valid_vy = INT_MIN;

    for (int vx0 = 1; vx0 <= max_x; vx0++) {
        for (int vy0 = min_y; vy0 <= 1000; vy0++) {
            int x = 0, y = 0;
            int vx = vx0, vy = vy0;
            while (x <= max_x && y >= min_y) {
                x += vx;
                y += vy;
                if (vx > 0)
                    vx--;
                vy--;

                if (x >= min_x && x <= max_x && y >= min_y && y <= max_y) {
                    part2++;
                    if (vy0 > max_valid_vy)
                        max_valid_vy = vy0;
                    break;
                }
            }
        }
    }

    int part1 = max_valid_vy * (max_valid_vy + 1) / 2;

    printf("Part 1: %d\nPart 2: %d\n", part1, part2);
}
