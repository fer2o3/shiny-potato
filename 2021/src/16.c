#include "aoc.h"
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

// This was definitely not the cleanest way to solve this shit
int parse_packet(const char *hex, int pos, int *version_sum) {
    int version = get_bits(hex, pos, 3);
    int type = get_bits(hex, pos + 3, 3);
    *version_sum += version;
    pos += 6;

    if (type == 4) {
        while (get_bits(hex, pos, 1))
            pos += 5;
        return pos + 5;
    } else {
        int length_type = get_bits(hex, pos++, 1);
        if (length_type == 0) {
            int sub_len = get_bits(hex, pos, 15);
            pos += 15;
            int end = pos + sub_len;
            while (pos < end)
                pos = parse_packet(hex, pos, version_sum);
        } else {
            int sub_count = get_bits(hex, pos, 11);
            pos += 11;
            for (int i = 0; i < sub_count; i++)
                pos = parse_packet(hex, pos, version_sum);
        }
        return pos;
    }
}

void solve_16(char **lines, int line_count) {
    char *hex = lines[0];

    int part1 = 0;
    parse_packet(hex, 0, &part1);

    printf("Part 1: %d\nPart 2: %d\n", part1, 0);
}
