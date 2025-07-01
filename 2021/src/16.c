#include "aoc.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int hex_to_val(char c) { return c <= '9' ? c - '0' : c - 'A' + 10; }

int get_bits(const char *hex, int pos, int len) {
    int val = 0;
    for (int i = 0; i < len; i++) {
        int hex_idx = (pos + i) / 4;
        int bit_idx = 3 - ((pos + i) % 4);
        val = (val << 1) | ((hex_to_val(hex[hex_idx]) >> bit_idx) & 1);
    }
    return val;
}

unsigned long long parse_packet(const char *hex, int *pos, int *version_sum) {
    int version = get_bits(hex, *pos, 3);
    int type = get_bits(hex, *pos + 3, 3);
    *version_sum += version;
    *pos += 6;

    if (type == 4) {
        unsigned long long val = 0;
        while (get_bits(hex, *pos, 1)) {
            val = (val << 4) | get_bits(hex, *pos + 1, 4);
            *pos += 5;
        }
        val = (val << 4) | get_bits(hex, *pos + 1, 4);
        *pos += 5;
        return val;
    }

    unsigned long long vals[1000];
    int count = 0;

    if (get_bits(hex, (*pos)++, 1) == 0) {
        int end = *pos + 15 + get_bits(hex, *pos, 15);
        *pos += 15;
        while (*pos < end)
            vals[count++] = parse_packet(hex, pos, version_sum);
    } else {
        int sub_count = get_bits(hex, *pos, 11);
        *pos += 11;
        for (int i = 0; i < sub_count; i++)
            vals[count++] = parse_packet(hex, pos, version_sum);
    }

    unsigned long long result = vals[0];
    switch (type) {
    case 0:
        for (int i = 1; i < count; i++)
            result += vals[i];
        break;
    case 1:
        for (int i = 1; i < count; i++)
            result *= vals[i];
        break;
    case 2:
        for (int i = 1; i < count; i++)
            if (vals[i] < result)
                result = vals[i];
        break;
    case 3:
        for (int i = 1; i < count; i++)
            if (vals[i] > result)
                result = vals[i];
        break;
    case 5:
        result = vals[0] > vals[1];
        break;
    case 6:
        result = vals[0] < vals[1];
        break;
    case 7:
        result = vals[0] == vals[1];
        break;
    }
    return result;
}

void solve_16(char **lines, int line_count) {
    (void)line_count; // This shit is just to suppress warning for now
    char *hex = lines[0];
    int part1 = 0, pos = 0;
    unsigned long long part2 = parse_packet(hex, &pos, &part1);
    printf("Part 1: %d\nPart 2: %llu\n", part1, part2);
}
