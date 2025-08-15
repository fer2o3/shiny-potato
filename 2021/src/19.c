#include "aoc.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int x, y, z;
} Point;

typedef struct {
    Point beacons[50];
    int beacon_count;
    Point position;
    int found;
} Scanner;

void rotate(Point *p, int rotation) {
    int x = p->x, y = p->y, z = p->z;
    switch (rotation) {
    case 0:
        *p = (Point){x, y, z};
        break;
    case 1:
        *p = (Point){x, z, -y};
        break;
    case 2:
        *p = (Point){x, -y, -z};
        break;
    case 3:
        *p = (Point){x, -z, y};
        break;
    case 4:
        *p = (Point){y, -x, z};
        break;
    case 5:
        *p = (Point){y, z, x};
        break;
    case 6:
        *p = (Point){y, x, -z};
        break;
    case 7:
        *p = (Point){y, -z, -x};
        break;
    case 8:
        *p = (Point){-x, -y, z};
        break;
    case 9:
        *p = (Point){-x, z, y};
        break;
    case 10:
        *p = (Point){-x, y, -z};
        break;
    case 11:
        *p = (Point){-x, -z, -y};
        break;
    case 12:
        *p = (Point){-y, x, z};
        break;
    case 13:
        *p = (Point){-y, z, -x};
        break;
    case 14:
        *p = (Point){-y, -x, -z};
        break;
    case 15:
        *p = (Point){-y, -z, x};
        break;
    case 16:
        *p = (Point){z, y, -x};
        break;
    case 17:
        *p = (Point){z, x, y};
        break;
    case 18:
        *p = (Point){z, -y, x};
        break;
    case 19:
        *p = (Point){z, -x, -y};
        break;
    case 20:
        *p = (Point){-z, -y, -x};
        break;
    case 21:
        *p = (Point){-z, x, -y};
        break;
    case 22:
        *p = (Point){-z, y, x};
        break;
    case 23:
        *p = (Point){-z, -x, y};
        break;
    }
}

int equal(Point a, Point b) { return a.x == b.x && a.y == b.y && a.z == b.z; }

Point sub(Point a, Point b) { return (Point){a.x - b.x, a.y - b.y, a.z - b.z}; }

int try_match(Scanner *ref, Scanner *other) {
    for (int rot = 0; rot < 24; rot++) {
        Point rotated[50];
        for (int i = 0; i < other->beacon_count; i++) {
            rotated[i] = other->beacons[i];
            rotate(&rotated[i], rot);
        }

        for (int i = 0; i < ref->beacon_count; i++) {
            for (int j = 0; j < other->beacon_count; j++) {
                Point delta = sub(rotated[j], ref->beacons[i]);

                Point translated[50];
                for (int k = 0; k < other->beacon_count; k++) {
                    translated[k] = sub(rotated[k], delta);
                }

                int matches = 0;
                for (int k = 0; k < other->beacon_count; k++) {
                    for (int l = 0; l < ref->beacon_count; l++) {
                        if (equal(translated[k], ref->beacons[l])) {
                            matches++;
                            break;
                        }
                    }
                }

                if (matches >= 12) {
                    other->position = delta;
                    for (int k = 0; k < other->beacon_count; k++) {
                        other->beacons[k] = translated[k];
                    }
                    return 1;
                }
            }
        }
    }
    return 0;
}

void solve_19(char **lines, int line_count) {
    Scanner scanners[50];
    int scanner_count = 0;
    int current_scanner = -1;

    for (int i = 0; i < line_count; i++) {
        if (strstr(lines[i], "scanner")) {
            current_scanner++;
            scanners[current_scanner].beacon_count = 0;
            scanners[current_scanner].found = 0;
            scanners[current_scanner].position = (Point){0, 0, 0};
        } else if (strlen(lines[i]) > 0) {
            Point p;
            sscanf(lines[i], "%d,%d,%d", &p.x, &p.y, &p.z);
            scanners[current_scanner]
                .beacons[scanners[current_scanner].beacon_count++] = p;
        }
    }
    scanner_count = current_scanner + 1;

    scanners[0].found = 1;
    int found_count = 1;

    while (found_count < scanner_count) {
        for (int i = 0; i < scanner_count; i++) {
            if (!scanners[i].found)
                continue;

            for (int j = 0; j < scanner_count; j++) {
                if (scanners[j].found || i == j)
                    continue;

                if (try_match(&scanners[i], &scanners[j])) {
                    scanners[j].found = 1;
                    found_count++;
                    break;
                }
            }
        }
    }

    Point unique_beacons[2000];
    int part1 = 0;

    for (int i = 0; i < scanner_count; i++) {
        for (int j = 0; j < scanners[i].beacon_count; j++) {
            int is_unique = 1;
            for (int k = 0; k < part1; k++) {
                if (equal(scanners[i].beacons[j], unique_beacons[k])) {
                    is_unique = 0;
                    break;
                }
            }
            if (is_unique) {
                unique_beacons[part1++] = scanners[i].beacons[j];
            }
        }
    }

    int part2 = 0;
    for (int i = 0; i < scanner_count; i++) {
        for (int j = i + 1; j < scanner_count; j++) {
            int manhattan =
                abs(scanners[i].position.x - scanners[j].position.x) +
                abs(scanners[i].position.y - scanners[j].position.y) +
                abs(scanners[i].position.z - scanners[j].position.z);
            if (manhattan > part2) {
                part2 = manhattan;
            }
        }
    }

    printf("Part 1: %d\nPart 2: %d\n", part1, part2);
}
