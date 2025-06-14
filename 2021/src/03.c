#include <stdio.h>
#include <string.h>
#include "aoc.h"

#define STR_LEN 12

struct binary {
    int valid;
    char value[STR_LEN + 1];
};

int get_power_consumption(struct binary data[], int data_size) {
    int ones[STR_LEN] = {0};
    for (int i = 0; i < data_size; i++)
        for (int j = 0; j < STR_LEN; j++)
            if (data[i].value[j] == '1') ones[j]++;

    int gamma = 0, epsilon = 0;
    for (int i = 0; i < STR_LEN; i++) {
        if (ones[i] > data_size / 2) 
            gamma |= 1 << (STR_LEN - 1 - i);
        else 
            epsilon |= 1 << (STR_LEN - 1 - i);
    }

    return gamma * epsilon;
}

int get_rating(struct binary data[], int data_size, int oxygen) {
    int valids = data_size, index = 0;

    while (valids > 1) {
        int ones = 0;
        for (int i = 0; i < data_size; i++)
            if (data[i].valid && data[i].value[index] == '1') ones++;

        char keep = ((ones >= valids - ones) == oxygen) + '0';

        for (int i = 0; i < data_size; i++) {
            if (data[i].valid && data[i].value[index] != keep) {
                data[i].valid = 0;
                valids--;
            }
        }
        index++;
    }

    for (int i = 0; i < data_size; i++) {
        if (data[i].valid) {
            int res = 0;
            for (int j = 0; j < STR_LEN; j++)
                if (data[i].value[j] == '1') res |= 1 << (STR_LEN - 1 - j);
            return res;
        }
    }

    return 0;
}

void solve_03(char **lines, int line_count) {
    struct binary data[1024];

    for (int i = 0; i < line_count; i++) {
        data[i].valid = 1;
        strcpy(data[i].value, lines[i]);
    }

    int part1 = get_power_consumption(data, line_count);
    int oxygen = get_rating(data, line_count, 1);

    for (int i = 0; i < line_count; i++) data[i].valid = 1;
    int co2 = get_rating(data, line_count, 0);

    printf("Part 1: %d\nPart 2: %d\n", part1, oxygen * co2);
}
