#include "aoc.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct SnailNumber {
    int value;
    struct SnailNumber *left;
    struct SnailNumber *right;
} SnailNumber;

SnailNumber *regular(int value) {
    SnailNumber *num = malloc(sizeof(SnailNumber));
    num->value = value;
    num->left = NULL;
    num->right = NULL;
    return num;
}

SnailNumber *pair(SnailNumber *left, SnailNumber *right) {
    SnailNumber *num = malloc(sizeof(SnailNumber));
    num->value = -1;
    num->left = left;
    num->right = right;
    return num;
}

SnailNumber *parse(const char *str, int *pos) {
    if (str[*pos] == '[') {
        (*pos)++;
        SnailNumber *left = parse(str, pos);
        (*pos)++;
        SnailNumber *right = parse(str, pos);
        (*pos)++;
        return pair(left, right);
    } else {
        int value = 0;
        while (str[*pos] >= '0' && str[*pos] <= '9') {
            value = value * 10 + (str[*pos] - '0');
            (*pos)++;
        }
        return regular(value);
    }
}

void free_number(SnailNumber *num) {
    if (num) {
        if (num->value < 0) {
            free_number(num->left);
            free_number(num->right);
        }
        free(num);
    }
}

int add_left(SnailNumber *num, int val) {
    if (num->value >= 0) {
        num->value += val;
        return 1;
    } else {
        return add_left(num->left, val) || add_left(num->right, val);
    }
}

int add_right(SnailNumber *num, int val) {
    if (num->value >= 0) {
        num->value += val;
        return 1;
    } else {
        return add_right(num->right, val) || add_right(num->left, val);
    }
}

int explode(SnailNumber *num, int depth, int *left, int *right, int *exploded) {
    if (num->value >= 0) {
        return 0;
    }

    if (depth >= 4 && !*exploded) {
        *left = num->left->value;
        *right = num->right->value;
        *exploded = 1;

        free_number(num->left);
        free_number(num->right);
        num->value = 0;
        num->left = NULL;
        num->right = NULL;
        return 1;
    }

    if (explode(num->left, depth + 1, left, right, exploded)) {
        add_left(num->right, *right);
        *right = 0;
        return 1;
    }

    if (explode(num->right, depth + 1, left, right, exploded)) {
        add_right(num->left, *left);
        *left = 0;
        return 1;
    }

    return 0;
}

int split(SnailNumber *num) {
    if (num->value >= 0) {
        if (num->value >= 10) {
            int left = num->value / 2;
            int right = (num->value + 1) / 2;
            num->value = -1;
            num->left = regular(left);
            num->right = regular(right);
            return 1;
        }
        return 0;
    } else {
        return split(num->left) || split(num->right);
    }
}

void print_number(SnailNumber *num) {
    if (num->value >= 0) {
        printf("%d", num->value);
    } else {
        printf("[");
        print_number(num->left);
        printf(",");
        print_number(num->right);
        printf("]");
    }
}

int reduce(SnailNumber *num) {
    int changed = 1;
    while (changed) {
        changed = 0;

        int left = 0, right = 0;
        int exploded = 0;
        if (explode(num, 0, &left, &right, &exploded)) {
            changed = 1;
            continue;
        }
        if (split(num)) {
            changed = 1;
            continue;
        }
    }

    return 1;
}

int magnitude(SnailNumber *num) {
    if (num->value >= 0) {
        return num->value;
    } else {
        return 3 * magnitude(num->left) + 2 * magnitude(num->right);
    }
}

SnailNumber *copy(SnailNumber *num) {
    if (num->value >= 0)
        return regular(num->value);
    else {
        return pair(copy(num->left), copy(num->right));
    }
}

SnailNumber *add(SnailNumber *left, SnailNumber *right) {
    SnailNumber *res = pair(copy(left), copy(right));
    reduce(res);
    return res;
}

void solve_18(char **lines, int line_count) {
    SnailNumber **numbers = malloc(line_count * sizeof(SnailNumber *));
    for (int i = 1; i < line_count; i++) {
        int pos = 0;
        numbers[i] = parse(lines[i], &pos);
    }

    int pos = 0;
    numbers[0] = parse(lines[0], &pos); // Fucking warnings
    SnailNumber *sum = copy(numbers[0]);
    for (int i = 1; i < line_count; i++) {
        SnailNumber *old = sum;
        sum = add(sum, numbers[i]);
        free_number(old);
    }

    int part1 = magnitude(sum);
    free_number(sum);

    int part2 = 0;
    for (int i = 0; i < line_count; i++) {
        for (int j = 0; j < line_count; j++) {
            if (i != j) {
                SnailNumber *temp = add(numbers[i], numbers[j]);
                int mag = magnitude(temp);
                if (mag > part2) {
                    part2 = mag;
                }
                free_number(temp);
            }
        }
    }

    for (int i = 0; i < line_count; i++) {
        free_number(numbers[i]);
    }
    free(numbers);

    printf("Part 1: %d\nPart 2: %d\n", part1, part2);
}
