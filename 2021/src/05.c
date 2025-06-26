#include "aoc.h"
#include <stdio.h>

#define GRID_SIZE 1000

struct line {
    int x1, y1, x2, y2;
};

void plot_line(struct line *line, int grid[GRID_SIZE][GRID_SIZE]) {
    int x = line->x1, y = line->y1;
    int dx = (x < line->x2) ? 1 : (x > line->x2) ? -1 : 0;
    int dy = (y < line->y2) ? 1 : (y > line->y2) ? -1 : 0;

    do {
        grid[x][y]++;
        x += dx;
        y += dy;
    } while (x != line->x2 || y != line->y2);
    grid[line->x2][line->y2]++;
}

int count_intersections(int grid[GRID_SIZE][GRID_SIZE]) {
    int count = 0;
    for (int i = 0; i < GRID_SIZE; i++)
        for (int j = 0; j < GRID_SIZE; j++)
            if (grid[i][j] > 1)
                count++;
    return count;
}

void solve_05(char **lines, int line_count) {
    static int grid1[GRID_SIZE][GRID_SIZE] = {0};
    static int grid2[GRID_SIZE][GRID_SIZE] = {0};

    for (int i = 0; i < line_count; i++) {
        struct line l;
        sscanf(lines[i], "%d,%d -> %d,%d", &l.x1, &l.y1, &l.x2, &l.y2);

        if (l.x1 == l.x2 || l.y1 == l.y2)
            plot_line(&l, grid1);

        plot_line(&l, grid2);
    }

    printf("Part 1: %d\nPart 2: %d\n", count_intersections(grid1),
           count_intersections(grid2));
}
