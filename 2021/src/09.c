#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aoc.h"

int is_low_point(char grid[][200], int rows, int cols, int r, int c) {
    int height = grid[r][c] - '0';

    int directions[4][2] = {{-1,0}, {1,0}, {0,-1}, {0,1}};

    for (int i = 0; i < 4; i++) {
        int nr = r + directions[i][0];
        int nc = c + directions[i][1];

        if (nr < 0 || nr >= rows || nc < 0 || nc >= cols) continue;

        if (grid[nr][nc] - '0' <= height) return 0;
    }

    return 1;
}

void solve_09(char **lines, int line_count) {
    char grid[200][200];
    int rows = line_count;
    int cols = strlen(lines[0]);

    for (int i = 0; i < rows; i++) {
        strcpy(grid[i], lines[i]);
    }

    int part1 = 0, part2 = 0;

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if (is_low_point(grid, rows, cols, r, c)) {
                part1 += (grid[r][c] - '0') + 1;
            }
        }
    }
    
    printf("Part 1: %d\nPart 2: %d\n", part1, part2);
}
