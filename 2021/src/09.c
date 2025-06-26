#include "aoc.h"
#include <stdio.h>
#include <string.h>

int is_low_point(char grid[][200], int rows, int cols, int r, int c) {
    int height = grid[r][c] - '0';
    int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    for (int i = 0; i < 4; i++) {
        int nr = r + dirs[i][0], nc = c + dirs[i][1];
        if (nr >= 0 && nr < rows && nc >= 0 && nc < cols) {
            if (grid[nr][nc] - '0' <= height)
                return 0;
        }
    }
    return 1;
}

int flood_fill(char grid[][200], int rows, int cols, int r, int c) {
    if (r < 0 || r >= rows || c < 0 || c >= cols || grid[r][c] == '9')
        return 0;

    grid[r][c] = '9';
    return 1 + flood_fill(grid, rows, cols, r - 1, c) +
           flood_fill(grid, rows, cols, r + 1, c) +
           flood_fill(grid, rows, cols, r, c - 1) +
           flood_fill(grid, rows, cols, r, c + 1);
}

void update_top3(int top3[3], int val) {
    if (val <= top3[0])
        return;

    if (val > top3[2]) {
        top3[0] = top3[1];
        top3[1] = top3[2];
        top3[2] = val;
    } else if (val > top3[1]) {
        top3[0] = top3[1];
        top3[1] = val;
    } else {
        top3[0] = val;
    }
}

void solve_09(char **lines, int line_count) {
    char grid[200][200];
    int rows = line_count, cols = strlen(lines[0]);
    int top3[3] = {0, 0, 0};
    int part1 = 0;

    for (int i = 0; i < rows; i++)
        strcpy(grid[i], lines[i]);

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if (is_low_point(grid, rows, cols, r, c)) {
                part1 += (grid[r][c] - '0') + 1;
                int basin_size = flood_fill(grid, rows, cols, r, c);
                update_top3(top3, basin_size);
            }
        }
    }

    printf("Part 1: %d\nPart 2: %d\n", part1, top3[0] * top3[1] * top3[2]);
}
