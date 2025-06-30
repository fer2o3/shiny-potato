#include "aoc.h"
#include <limits.h>
#include <stdio.h>
#include <string.h>

char rules[26][26];
long long pairs[26][26];

long long score() {
    long long counts[26] = {0};

    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < 26; j++) {
            counts[i] += pairs[i][j];
        }
    }

    long long min_count = LLONG_MAX, max_count = 0;
    for (int i = 0; i < 26; i++) {
        if (counts[i] > 0) {
            if (counts[i] < min_count)
                min_count = counts[i];
            if (counts[i] > max_count)
                max_count = counts[i];
        }
    }
    return max_count - min_count;
}

void solve_14(char **lines, int line_count) {
    memset(rules, 0, sizeof(rules));
    memset(pairs, 0, sizeof(pairs));

    char *template = lines[0];
    int len = strlen(template);

    for (int i = 0; i < len - 1; i++) {
        pairs[template[i] - 'A'][template[i + 1] - 'A']++;
    }

    for (int i = 2; i < line_count; i++) {
        char pair[3], insert;
        sscanf(lines[i], "%2s -> %c", pair, &insert);
        rules[pair[0] - 'A'][pair[1] - 'A'] = insert - 'A';
    }

    long long part1 = 0;

    for (int step = 0; step < 40; step++) {
        long long new_counts[26][26] = {0};

        for (int i = 0; i < 26; i++) {
            for (int j = 0; j < 26; j++) {
                if (pairs[i][j] > 0 && rules[i][j] >= 0) {
                    int c = rules[i][j];
                    new_counts[i][c] += pairs[i][j];
                    new_counts[c][j] += pairs[i][j];
                }
            }
        }

        memcpy(pairs, new_counts, sizeof(pairs));

        if (step == 9) {
            pairs[template[len - 1] - 'A'][0]++;
            part1 = score();
            pairs[template[len - 1] - 'A'][0]--;
        }
    }

    pairs[template[len - 1] - 'A'][0]++;
    long long part2 = score();

    printf("Part 1: %lld\nPart 2: %lld\n", part1, part2);
}
