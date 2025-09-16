#include "aoc.h"
#include <stdio.h>

typedef struct {
    int div_z;
    int add_x;
    int add_y;
} Block;

void parse_blocks(char **lines, int line_count, Block blocks[14]) {
    int block_idx = 0;

    for (int i = 0; i < line_count; i += 18) {
        sscanf(lines[i + 4], "div z %d", &blocks[block_idx].div_z);
        sscanf(lines[i + 5], "add x %d", &blocks[block_idx].add_x);
        sscanf(lines[i + 15], "add y %d", &blocks[block_idx].add_y);
        block_idx++;
    }
}

long find_model_number(Block blocks[14], int flag) {
    long result[14] = {0};
    long stack[14];
    int stack_idx = 0;

    for (int i = 0; i < 14; i++) {
        if (blocks[i].div_z == 1) {
            stack[stack_idx++] = i;
        } else {
            int j = stack[--stack_idx];
            int diff = blocks[j].add_y + blocks[i].add_x;

            if (flag) {
                if (diff >= 0) {
                    result[j] = 9 - diff;
                    result[i] = 9;
                } else {
                    result[j] = 9;
                    result[i] = 9 + diff;
                }
            } else {
                if (diff >= 0) {
                    result[j] = 1;
                    result[i] = 1 + diff;
                } else {
                    result[j] = 1 - diff;
                    result[i] = 1;
                }
            }
        }
    }

    long model = 0;
    for (int i = 0; i < 14; i++) {
        model = model * 10 + result[i];
    }

    return model;
}

void solve_24(char **lines, int line_count) {
    Block blocks[14];
    parse_blocks(lines, line_count, blocks);

    long part1 = find_model_number(blocks, 1);
    long part2 = find_model_number(blocks, 0);

    printf("Part 1: %ld\nPart 2: %ld\n", part1, part2);
}
