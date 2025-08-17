#include "aoc.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int roll(int dice) {
    int res = 0;
    for (int i = 0; i < 3; i++)
        res += ((dice - 1 + i) % 100) + 1;
    return res;
}

void solve_21(char **lines, int line_count) {
    int p1, p2;
    sscanf(lines[0], "Player 1 starting position: %d", &p1);
    sscanf(lines[1], "Player 2 starting position: %d", &p2);

    int score1 = 0, score2 = 0;
    int dice = 1;
    int rolls = 0;
    while (1) {
        p1 = (p1 + roll(dice) - 1) % 10 + 1;
        dice = (dice + 2) % 100 + 1;
        score1 += p1;
        rolls += 3;
        if (score1 >= 1000)
            break;

        p2 = (p2 + roll(dice) - 1) % 10 + 1;
        score2 += p2;
        dice = (dice + 2) % 100 + 1;
        rolls += 3;
        if (score2 >= 1000)
            break;
    }

    long part1 = score1 >= 1000 ? score2 * rolls : score1 * rolls;

    int part2 = 0;
    printf("Part 1: %ld\nPart 2: %d\n", part1, part2);
}
