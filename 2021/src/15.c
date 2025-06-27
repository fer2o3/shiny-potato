#include "aoc.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char grid[500][500];
int dist[250000];
char visited[250000];

int find_min(int size) {
    int min = INT_MAX, index = -1;
    for (int i = 0; i < size; i++) {
        if (!visited[i] && dist[i] < min) {
            min = dist[i];
            index = i;
        }
    }
    return index;
}

int dijkstra(int size) {
    int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    int target = size * size - 1;

    while (1) {
        int current = find_min(size * size);
        if (current == -1 || current == target)
            break;

        visited[current] = 1;
        int r = current / size, c = current % size;

        for (int i = 0; i < 4; i++) {
            int nr = r + dirs[i][0], nc = c + dirs[i][1];
            if (nr >= 0 && nr < size && nc >= 0 && nc < size) {
                int neighbor = nr * size + nc;
                if (!visited[neighbor]) {
                    int new_dist = dist[current] + (grid[nr][nc]);
                    if (new_dist < dist[neighbor]) {
                        dist[neighbor] = new_dist;
                    }
                }
            }
        }
    }
    return dist[target];
}

void solve_15(char **lines, int line_count) {
    int full_size = line_count * 5;

    for (int r = 0; r < 5; r++) {
        for (int c = 0; c < 5; c++) {
            for (int i = 0; i < line_count; i++) {
                for (int j = 0; j < line_count; j++) {
                    int risk = (lines[i][j] - '0' + r + c - 1) % 9 + 1;
                    grid[r * line_count + i][c * line_count + j] = risk;
                }
            }
        }
    }

    memset(visited, 0, full_size * full_size);
    for (int i = 0; i < full_size * full_size; i++) {
        dist[i] = INT_MAX;
    }
    dist[0] = 0;

    dijkstra(full_size);
    int part1 = dist[(line_count - 1) * full_size + (line_count - 1)];
    int part2 = dist[full_size * full_size - 1];

    printf("Part 1: %d\nPart 2: %d\n", part1, part2);
}
