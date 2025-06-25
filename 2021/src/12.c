#include <stdio.h>
#include <string.h>
#include "aoc.h"

int graph[50][20];
int conn_count[50] = {0};
char names[50][10];
int name_count = 0;

int get_id(char *name) {
    for (int i = 0; i < name_count; i++) {
        if (strcmp(names[i], name) == 0) return i;
    }
    strcpy(names[name_count], name);
    return name_count++;
}

int dfs(int current, char visited[], int can_double) {
    if (current == 1) return 1;

    int paths = 0;
    int is_small = names[current][0] >= 'a';

    if (is_small) visited[current]++;

    for (int i = 0; i < conn_count[current]; i++) {
        int next = graph[current][i];
        if (next == 0) continue;

        int next_small = names[next][0] >= 'a';

        if (next_small && visited[next]) {
            if (!can_double || next == 0 || next == 1) continue;
            paths += dfs(next, visited, 0);
        } else {
            paths += dfs(next, visited, can_double);
        }
    }

    if (is_small) visited[current]--;
    return paths;
}

void solve_12(char **lines, int line_count) {
    get_id("start");
    get_id("end");

    for (int i = 0; i < line_count; i++) {
        char *dash = strchr(lines[i], '-');
        *dash = '\0';

        int id1 = get_id(lines[i]);
        int id2 = get_id(dash + 1);

        graph[id1][conn_count[id1]++] = id2;
        graph[id2][conn_count[id2]++] = id1;
    }

    char visited[50] = {0};
    int part1 = dfs(0, visited, 0);

    memset(visited, 0, sizeof visited);
    int part2 = dfs(0, visited, 1);

    printf("Part 1: %d\nPart 2: %d\n", part1, part2);
}
