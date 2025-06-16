#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include "aoc.h"

typedef void (*day_func_t)(char **lines, int line_count);

static day_func_t day_functions[] = {
    solve_01, solve_02, solve_03, solve_04, solve_05,
    solve_06, solve_07, solve_08, solve_09, solve_10,
    solve_11, solve_12, solve_13, solve_14, solve_15,
    solve_16, solve_17, solve_18, solve_19, solve_20,
    solve_21, solve_22, solve_23, solve_24, solve_25
};

char **read_lines(const char *filename, int *line_count) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        return NULL;
    }
    
    *line_count = 0;
    char ch;
    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n') (*line_count)++;
    }
    
    fseek(file, -1, SEEK_END);
    if (fgetc(file) != '\n') (*line_count)++;
    
    rewind(file);
    
    char **lines = malloc(*line_count * sizeof(char *));
    if (!lines) {
        fclose(file);
        return NULL;
    }
    
    char buffer[10000];
    int i = 0;
    while (fgets(buffer, sizeof(buffer), file) && i < *line_count) {
        int len = strlen(buffer);
        if (len > 0 && buffer[len-1] == '\n') {
            buffer[len-1] = '\0';
        }
        
        lines[i] = malloc(strlen(buffer) + 1);
        strcpy(lines[i], buffer);
        i++;
    }
    
    fclose(file);
    return lines;
}

void free_lines(char **lines, int line_count) {
    for (int i = 0; i < line_count; i++) {
        free(lines[i]);
    }
    free(lines);
}

int file_exists(const char *filename) {
    struct stat buffer;
    return (stat(filename, &buffer) == 0);
}

void run_day(int day, const char *input_type) {
    char filename[256];
    if (strcmp(input_type, "test") == 0) {
        snprintf(filename, sizeof(filename), "test_inputs/%02d.in", day);
    } else {
        snprintf(filename, sizeof(filename), "inputs/%02d.in", day);
    }
    
    if (!file_exists(filename)) {
        printf("Day %02d: Input file not found\n", day);
        return;
    }
    
    int line_count;
    char **lines = read_lines(filename, &line_count);
    if (!lines) {
        printf("Day %02d: Failed to read input file\n", day);
        return;
    }
    
    printf("Day %02d:\n", day);
    fflush(stdout);
    
    clock_t start = clock();
    day_functions[day - 1](lines, line_count);
    clock_t end = clock();
    
    double time_ms = ((double)(end - start) / CLOCKS_PER_SEC) * 1000.0;
    printf(" (%.2fms)\n", time_ms);
    
    free_lines(lines, line_count);
}

void run_all_days(const char *input_type) {
    printf("Running all days...\n");
    for (int day = 1; day <= 25; day++) {
        run_day(day, input_type);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <day|all> [input_type]\n", argv[0]);
        return 1;
    }
    
    const char *input_type = (argc > 2) ? argv[2] : "input";
    
    if (strcmp(argv[1], "all") == 0) {
        run_all_days(input_type);
    } else {
        int day = atoi(argv[1]);
        if (day < 1 || day > 25) {
            printf("Day must be between 1 and 25\n");
            return 1;
        }
        run_day(day, input_type);
    }
    
    return 0;
}
