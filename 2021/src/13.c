#include "aoc.h"
#include <ctype.h>
#include <stdio.h>

int count_dots(char paper[1500][1500], int w, int h) {
    int res = 0;
    for (int i = 0; i < h; i++)
        for (int j = 0; j < w; j++)
            res += paper[i][j];
    return res;
}

void solve_13(char **lines, int line_count) {
    char paper[1500][1500] = {{0}};
    int w = 0, h = 0, part1 = 0, first_fold = 1;

    for (int i = 0; i < line_count; i++) {
        if (isdigit(lines[i][0])) {
            int x, y;
            sscanf(lines[i], "%d,%d", &x, &y);
            paper[y][x] = 1;
            if (x >= w)
                w = x + 1;
            if (y >= h)
                h = y + 1;
        } else if (lines[i][0] == 'f') {
            char axis;
            int val;
            sscanf(lines[i], "fold along %c=%d", &axis, &val);

            if (axis == 'y') {
                for (int k = 0; k < val; k++)
                    for (int l = 0; l < w; l++)
                        paper[k][l] |= paper[val * 2 - k][l];
                h = val;
            } else {
                for (int k = 0; k < h; k++)
                    for (int l = 0; l < val; l++)
                        paper[k][l] |= paper[k][val * 2 - l];
                w = val;
            }

            if (first_fold) {
                part1 = count_dots(paper, w, h);
                first_fold = 0;
            }
        }
    }

    printf("Part 1: %d\nPart 2:\n", part1);
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++)
            printf("%c", paper[i][j] ? '#' : ' ');
        printf("\n");
    }
}
