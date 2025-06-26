#include "aoc.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char grid[100][100];
int dist[10000];
char visited[10000];

int find_min() {
    int min = INT_MAX, index = -1;
    for (int i = 0; i < 10000; i++) {
        if (!visited[i] && dist[i] < min) {
            min = dist[i];
            index = i;
        }
    }
    return index;
}

int dijkstra() {
    int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    while (1) {
        int current = find_min();
        if (current == -1 || current == 9999)
            break;

        visited[current] = 1;
        int r = current / 100, c = current % 100;

        for (int i = 0; i < 4; i++) {
            int nr = r + dirs[i][0], nc = c + dirs[i][1];
            if (nr >= 0 && nr < 100 && nc >= 0 && nc < 100) {
                int neighbor = nr * 100 + nc;
                if (!visited[neighbor]) {
                    int new_dist = dist[current] + (grid[nr][nc] - '0');
                    if (new_dist < dist[neighbor]) {
                        dist[neighbor] = new_dist;
                    }
                }
            }
        }
    }
    return dist[9999];
}

void solve_15(char **lines, int line_count) {
    for (int i = 0; i < line_count; i++) {
        for (int j = 0; j < 100; j++) {
            grid[i][j] = lines[i][j];
        }
    }

    for (int i = 0; i < 10000; i++) {
        dist[i] = INT_MAX;
    }
    dist[0] = 0;
    memset(visited, 0, sizeof(visited));

    printf("Part 1: %d\nPart 2: %d\n", dijkstra(), 0);
}
