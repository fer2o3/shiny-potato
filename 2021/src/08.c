#include "aoc.h"
#include <stdio.h>
#include <string.h>

int to_mask(char *str) {
    int mask = 0;
    while (*str)
        mask |= 1 << (*str++ - 'a');
    return mask;
}

int popcount(int x) {
    int count = 0;
    while (x)
        count += x & 1, x >>= 1;
    return count;
}

void solve_08(char **lines, int line_count) {
    int part1 = 0, part2 = 0;

    for (int i = 0; i < line_count; i++) {
        char line_copy[200];
        strcpy(line_copy, lines[i]);
        char *outputs_str = strchr(line_copy, '|') + 2;
        *strchr(line_copy, '|') = '\0';

        int patterns[10], outputs[4];
        int pattern_count = 0, output_count = 0;

        char *token = strtok(line_copy, " ");
        while (token && pattern_count < 10) {
            patterns[pattern_count++] = to_mask(token);
            token = strtok(NULL, " ");
        }

        token = strtok(outputs_str, " ");
        while (token && output_count < 4) {
            outputs[output_count++] = to_mask(token);
            int len = strlen(token);
            if (len == 2 || len == 3 || len == 4 || len == 7)
                part1++;
            token = strtok(NULL, " ");
        }

        int digits[10] = {0};
        for (int j = 0; j < 10; j++) {
            int segments = popcount(patterns[j]);
            if (segments == 2)
                digits[1] = patterns[j];
            else if (segments == 3)
                digits[7] = patterns[j];
            else if (segments == 4)
                digits[4] = patterns[j];
            else if (segments == 7)
                digits[8] = patterns[j];
        }

        for (int j = 0; j < 10; j++) {
            if (popcount(patterns[j]) == 6) {
                if ((patterns[j] & digits[1]) != digits[1])
                    digits[6] = patterns[j];
                else if ((patterns[j] & digits[4]) == digits[4])
                    digits[9] = patterns[j];
                else
                    digits[0] = patterns[j];
            }
        }

        for (int j = 0; j < 10; j++) {
            if (popcount(patterns[j]) == 5) {
                if ((patterns[j] & digits[1]) == digits[1])
                    digits[3] = patterns[j];
                else if ((digits[6] & patterns[j]) == patterns[j])
                    digits[5] = patterns[j];
                else
                    digits[2] = patterns[j];
            }
        }

        int value = 0;
        for (int j = 0; j < 4; j++) {
            for (int k = 0; k < 10; k++) {
                if (outputs[j] == digits[k]) {
                    value = value * 10 + k;
                    break;
                }
            }
        }
        part2 += value;
    }

    printf("Part 1: %d\nPart 2: %d\n", part1, part2);
}
