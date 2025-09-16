#include "aoc.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cucumber_step(char grid[][200], int rows, int cols) {
    int flag = 0;
    char temp[200][200];

    for (int r = 0; r < rows; r++)
        for (int c = 0; c < cols; c++)
            temp[r][c] = grid[r][c];

    // EAST
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            int nc = (c + 1) % cols;
            if (grid[r][c] == '>' && grid[r][nc] == '.') {
                temp[r][c] = '.';
                temp[r][nc] = '>';
                flag = 1;
            }
        }
    }

    for (int r = 0; r < rows; r++)
        for (int c = 0; c < cols; c++)
            grid[r][c] = temp[r][c];

    for (int r = 0; r < rows; r++)
        for (int c = 0; c < cols; c++)
            temp[r][c] = grid[r][c];

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            int nr = (r + 1) % rows;
            if (grid[r][c] == 'v' && grid[nr][c] == '.') {
                temp[r][c] = '.';
                temp[nr][c] = 'v';
                flag = 1;
            }
        }
    }

    for (int r = 0; r < rows; r++)
        for (int c = 0; c < cols; c++)
            grid[r][c] = temp[r][c];

    return flag;
}

void solve_25(char **lines, int line_count) {
    char grid[200][200];
    int rows = line_count, cols = strlen(lines[0]);
    for (int i = 0; i < rows; i++)
        strcpy(grid[i], lines[i]);

    int part1 = 1;
    while (cucumber_step(grid, rows, cols)) {
        part1++;
    }

    printf("Part 1: %d\nPart 2: KACHOW !!!\n", part1);
}
