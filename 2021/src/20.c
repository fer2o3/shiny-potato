#include "aoc.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 250

void solve_20(char **lines, int line_count) {
    char *algorithm = lines[0];

    int original_height = line_count - 2;
    int original_width = strlen(lines[2]);

    char grid1[MAX_SIZE][MAX_SIZE];
    char grid2[MAX_SIZE][MAX_SIZE];

    char background = '.';

    int offset = (MAX_SIZE - original_width) / 2;

    for (int i = 0; i < MAX_SIZE; i++) {
        for (int j = 0; j < MAX_SIZE; j++) {
            grid1[i][j] = background;
        }
    }

    for (int i = 0; i < original_height; i++) {
        for (int j = 0; j < original_width; j++) {
            grid1[i + offset][j + offset] = lines[2 + i][j];
        }
    }

    char(*current)[MAX_SIZE] = grid1;
    char(*next)[MAX_SIZE] = grid2;

    int part1 = 0, part2 = 0;

    for (int iter = 0; iter < 50; iter++) {
        char new_background;
        if (background == '.') {
            new_background = algorithm[0];
        } else {
            new_background = algorithm[511];
        }

        for (int i = 1; i < MAX_SIZE - 1; i++) {
            for (int j = 1; j < MAX_SIZE - 1; j++) {
                int index = 0;
                for (int di = -1; di <= 1; di++) {
                    for (int dj = -1; dj <= 1; dj++) {
                        int ni = i + di;
                        int nj = j + dj;

                        char pixel;
                        if (ni < 0 || ni >= MAX_SIZE || nj < 0 ||
                            nj >= MAX_SIZE) {
                            pixel = background;
                        } else {
                            pixel = current[ni][nj];
                        }

                        index = (index << 1) + (pixel == '#' ? 1 : 0);
                    }
                }

                next[i][j] = algorithm[index];
            }
        }

        for (int i = 0; i < MAX_SIZE; i++) {
            next[i][0] = new_background;
            next[i][MAX_SIZE - 1] = new_background;
            next[0][i] = new_background;
            next[MAX_SIZE - 1][i] = new_background;
        }

        char(*temp)[MAX_SIZE] = current;
        current = next;
        next = temp;
        background = new_background;

        if (iter == 1) {
            for (int i = 0; i < MAX_SIZE; i++) {
                for (int j = 0; j < MAX_SIZE; j++) {
                    if (current[i][j] == '#') {
                        part1++;
                    }
                }
            }
        }
        if (iter == 49) {
            for (int i = 0; i < MAX_SIZE; i++) {
                for (int j = 0; j < MAX_SIZE; j++) {
                    if (current[i][j] == '#') {
                        part2++;
                    }
                }
            }
        }
    }

    printf("Part 1: %d\nPart 2: %d\n", part1, part2);
}
