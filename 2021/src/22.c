#include "aoc.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int state;
    int x1, x2;
    int y1, y2;
    int z1, z2;
} cuboid;

typedef struct {
    cuboid *data;
    int size;
    int cap;
} cuboidList;

void add_cuboid(cuboidList *list, cuboid c) {
    if (list->size == list->cap) {
        list->cap = list->cap ? list->cap * 2 : 16;
        list->data = realloc(list->data, list->cap * sizeof(cuboid));
    }
    list->data[list->size++] = c;
}

int parse_line(const char *line, cuboid *inst) {
    char state[4];

    sscanf(line, "%3s x=%d..%d,y=%d..%d,z=%d..%d", state, &inst->x1, &inst->x2,
           &inst->y1, &inst->y2, &inst->z1, &inst->z2);

    inst->state = (strcmp(state, "on") == 0) ? 1 : 0;
    return 1;
}

int intersect(const cuboid *a, const cuboid *b, cuboid *out) {
    out->x1 = (a->x1 > b->x1) ? a->x1 : b->x1;
    out->x2 = (a->x2 < b->x2) ? a->x2 : b->x2;
    out->y1 = (a->y1 > b->y1) ? a->y1 : b->y1;
    out->y2 = (a->y2 < b->y2) ? a->y2 : b->y2;
    out->z1 = (a->z1 > b->z1) ? a->z1 : b->z1;
    out->z2 = (a->z2 < b->z2) ? a->z2 : b->z2;
    return (out->x1 <= out->x2 && out->y1 <= out->y2 && out->z1 <= out->z2);
}

int subtract(const cuboid *a, const cuboid *b, cuboid *out) {
    cuboid inter;
    if (!intersect(a, b, &inter)) {
        out[0] = *a;
        return 1;
    }

    int count = 0;

    if (a->x1 <= inter.x1 - 1) {
        out[count++] =
            (cuboid){1, a->x1, inter.x1 - 1, a->y1, a->y2, a->z1, a->z2};
    }
    if (inter.x2 + 1 <= a->x2) {
        out[count++] =
            (cuboid){1, inter.x2 + 1, a->x2, a->y1, a->y2, a->z1, a->z2};
    }
    if (a->y1 <= inter.y1 - 1) {
        out[count++] =
            (cuboid){1, inter.x1, inter.x2, a->y1, inter.y1 - 1, a->z1, a->z2};
    }
    if (inter.y2 + 1 <= a->y2) {
        out[count++] =
            (cuboid){1, inter.x1, inter.x2, inter.y2 + 1, a->y2, a->z1, a->z2};
    }
    if (a->z1 <= inter.z1 - 1) {
        out[count++] = (cuboid){1,        inter.x1, inter.x2,    inter.y1,
                                inter.y2, a->z1,    inter.z1 - 1};
    }
    if (inter.z2 + 1 <= a->z2) {
        out[count++] = (cuboid){1,        inter.x1,     inter.x2, inter.y1,
                                inter.y2, inter.z2 + 1, a->z2};
    }

    return count;
}

long long volume(const cuboid *c) {
    return (long long)(c->x2 - c->x1 + 1) * (long long)(c->y2 - c->y1 + 1) *
           (long long)(c->z2 - c->z1 + 1);
}

void solve_22(char **lines, int line_count) {
    cuboid *instructions = malloc(line_count * sizeof(cuboid));

    for (int i = 0; i < line_count; i++) {
        parse_line(lines[i], &instructions[i]);
    }

    long long part1 = 0, part2 = 0;

    cuboidList active = {0};
    for (int i = 0; i < line_count; i++) {
        cuboid c = instructions[i];
        cuboidList next = {0};

        for (int j = 0; j < active.size; j++) {
            cuboid existing = active.data[j];
            cuboid leftovers[6];
            int count = subtract(&existing, &c, leftovers);
            for (int k = 0; k < count; k++) {
                add_cuboid(&next, leftovers[k]);
            }
        }

        if (c.state == 1) {
            add_cuboid(&next, c);
        }

        free(active.data);
        active = next;

        if (i == 19) {
            for (int j = 0; j < active.size; j++) {
                part1 += volume(&active.data[j]);
            }
        }
    }

    for (int i = 0; i < active.size; i++) {
        part2 += volume(&active.data[i]);
    }
    free(active.data);

    printf("Part 1: %lld\nPart 2: %lld\n", part1, part2);
}
