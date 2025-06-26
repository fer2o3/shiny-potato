#include "aoc.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BOARDS 128
#define BOARD_SIZE 25

struct GridNum {
    int flag;
    int value;
};

int checkBingo(struct GridNum board[BOARD_SIZE]) {
    for (int i = 0; i < 5; i++) {
        int row = 1, col = 1;
        for (int j = 0; j < 5; j++) {
            if (!board[i + j * 5].flag)
                row = 0;
            if (!board[j + i * 5].flag)
                col = 0;
        }
        if (row || col)
            return 1;
    }
    return 0;
}

int sumNotFlagged(struct GridNum board[BOARD_SIZE]) {
    int sum = 0;
    for (int i = 0; i < BOARD_SIZE; i++)
        if (!board[i].flag)
            sum += board[i].value;
    return sum;
}

void solve_04(char **lines, int line_count) {
    struct GridNum boards[MAX_BOARDS][BOARD_SIZE];
    int numbers[MAX_BOARDS];
    int numNumbers = 0, numBoards = 0;

    char *token = strtok(lines[0], ",");
    while (token) {
        numbers[numNumbers++] = atoi(token);
        token = strtok(NULL, ",");
    }

    int boardIndex = 0, cellIndex = 0;
    for (int i = 2; i < line_count; i++) {
        if (strlen(lines[i]) == 0)
            continue;

        char *num = strtok(lines[i], " ");
        while (num) {
            boards[boardIndex][cellIndex].value = atoi(num);
            boards[boardIndex][cellIndex].flag = 0;
            cellIndex++;
            num = strtok(NULL, " ");
        }

        if (cellIndex == BOARD_SIZE) {
            boardIndex++;
            cellIndex = 0;
        }
    }
    numBoards = boardIndex;

    int part1 = 0, part2 = 0;
    int won[MAX_BOARDS] = {0};
    int winners = 0;

    for (int num_i = 0; num_i < numNumbers && (!part1 || !part2); num_i++) {
        for (int board_i = 0; board_i < numBoards; board_i++) {
            if (won[board_i])
                continue;

            for (int val_i = 0; val_i < BOARD_SIZE; val_i++) {
                if (boards[board_i][val_i].value == numbers[num_i]) {
                    boards[board_i][val_i].flag = 1;
                    break;
                }
            }

            if (checkBingo(boards[board_i])) {
                won[board_i] = 1;
                winners++;
                int score = sumNotFlagged(boards[board_i]) * numbers[num_i];

                if (!part1)
                    part1 = score;
                if (winners == numBoards)
                    part2 = score;
            }
        }
    }

    printf("Part 1: %d\nPart 2: %d\n", part1, part2);
}
