#include "aoc.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    long p1;
    long p2;
} result;

result memo[11][11][21][21][2];
int memo_set[11][11][21][21][2];

int freq[10] = {0, 0, 0, 1, 3,
                6, 7, 6, 3, 1}; // this is to make the code more readable in my
                                // head, don't mind it

result quantum(int p1, int p2, int p1_score, int p2_score, int turn) {
    if (p1_score >= 21)
        return (result){1, 0};
    if (p2_score >= 21)
        return (result){0, 1};

    if (memo_set[p1][p2][p1_score][p2_score][turn])
        return memo[p1][p2][p1_score][p2_score][turn];

    result res = {0, 0};

    if (turn == 0) {
        for (int roll = 3; roll <= 9; roll++) {
            int new_pos = (p1 + roll - 1) % 10 + 1;
            int new_score = p1_score + new_pos;
            result sub = quantum(new_pos, p2, new_score, p2_score, 1);
            res.p1 += sub.p1 * freq[roll];
            res.p2 += sub.p2 * freq[roll];
        }
    } else {
        for (int roll = 3; roll <= 9; roll++) {
            int new_pos = (p2 + roll - 1) % 10 + 1;
            int new_score = p2_score + new_pos;
            result sub = quantum(p1, new_pos, p1_score, new_score, 0);
            res.p1 += sub.p1 * freq[roll];
            res.p2 += sub.p2 * freq[roll];
        }
    }

    memo[p1][p2][p1_score][p2_score][turn] = res;
    memo_set[p1][p2][p1_score][p2_score][turn] = 1;
    return res;
}

int roll(int dice) {
    int res = 0;
    for (int i = 0; i < 3; i++)
        res += ((dice - 1 + i) % 100) + 1;
    return res;
}

int classic(int p1, int p2) {
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

    return score1 >= 1000 ? score2 * rolls : score1 * rolls;
}

void solve_21(char **lines, int line_count) {
    int p1, p2;
    sscanf(lines[0], "Player 1 starting position: %d", &p1);
    sscanf(lines[1], "Player 2 starting position: %d", &p2);

    long part1 = classic(p1, p2);

    memset(memo_set, 0, sizeof(memo_set));
    result res = quantum(p1, p2, 0, 0, 0);
    long part2 = res.p1 > res.p2 ? res.p1 : res.p2;

    printf("Part 1: %ld\nPart 2: %ld\n", part1, part2);
}
