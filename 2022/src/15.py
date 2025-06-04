import re
from itertools import tee
import os


def pairwise(iterable):
    a, b = tee(iterable)
    next(b, None)
    return zip(a, b)


def part_one(beacons):
    # We Keep only the sensors that reach y = 2000000 
    first_compress = []
    for x, y, d in beacons:
        left = d - abs(2000000 - y)
        if left >= 0:
            first_compress.append((x, left))
    # We compress all our points into intervals
    second_compress = []
    for x, left in first_compress:
        second_compress.append((x - left, True))
        second_compress.append((x + left + 1, False))
    # We sort the values to make some of them overlap
    second_compress.sort()

    # We iterate through the values, making sure not to count twice areas that overlap
    res, inside = -1, 1
    for (prev, _), (x, start) in pairwise(second_compress):
        if inside > 0:
            res += x - prev
        inside += 1 if start else -1

    return res


def part_two(beacons):
    for x, y, d in beacons:
        for dist in range(d):
            for dir_x, dir_y in [(-1, -1), (-1, 1), (1, -1), (1, 1)]:
                bx, by = x + dir_x * dist, y + dir_y * (d + 1 - dist)
                if not (0 <= bx < 4000000 and 0 <= by < 4000000):
                    break
                if all(abs(bx - x) + abs(by - y) >= d for x, y, d in beacons):
                    return bx * 4000000 + by
    raise ValueError("Solution not found")

def main(input_dir):
    input_file_path = os.path.join(os.path.dirname(__file__), "../" + input_dir +"/15.in")
    
    with open(input_file_path, 'r') as f:
        data = f.read().splitlines()

    beacons = []

    p = r'Sensor at x=(-?\d+), y=(-?\d+): closest beacon is at x=(-?\d+), y=(-?\d+)'
    for line in data:
        caught = re.search(p, line)
        x, y, dx, dy = map(int, caught.groups())
        beacons.append((x, y, abs(x - dx) + abs(y - dy)))

    print(f"Part 1: {part_one(beacons)}")
    print(f"Part 2: {part_two(beacons)}")
