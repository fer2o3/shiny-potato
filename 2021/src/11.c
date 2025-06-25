#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aoc.h"

int flash(int grid[][10], int r, int c) {
    int flashes = 1;
    grid[r][c] = -9999;
    int dirs[8][2] = {
        {-1,0}, {1,0}, {0,-1}, {0,1}, 
        {1,1}, {-1,-1}, {1,-1}, {-1,1}
    };

    for (int i = 0; i < 8; i++) {
        int nr = r + dirs[i][0], nc = c + dirs[i][1];
        if (nr >= 0 && nr < 10 && nc >= 0 && nc < 10) {
            grid[nr][nc]++;
            if (grid[nr][nc] > 9) flashes += flash(grid, nr, nc);
        }
    }

    return flashes;
}

int step(int grid[][10]) {
    int flashes = 0;
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            grid[i][j]++;

    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            if (grid[i][j] > 9)
                flashes += flash(grid, i, j);

    int counter = 0;
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            if (grid[i][j] < 0) {
                grid[i][j] = 0;
                counter++;
            }

    return counter == 100 ? -1 : flashes;
}

void solve_11(char **lines, int line_count) {
    (void)line_count; // This shit is just to suppress warning for now

    int grid[10][10];
    int rows = 10, cols = 10;
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            grid[i][j] = lines[i][j] - '0';

    int part1 = 0, part2 = 0;

    int iter = 0, count = 0;
    while (!part2) {
        iter++;
        count = step(grid);
        if (iter <= 100) part1 += count;
        if (count == -1) part2 = iter;
    }

    printf("Part 1: %d\nPart 2: %d\n", part1, part2);
}
