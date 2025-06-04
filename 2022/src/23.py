from typing import List, Tuple
from collections import defaultdict
import os


def main(input_dir):
    input_file_path = os.path.join(os.path.dirname(__file__), "../" + input_dir +"/23.in")
    
    with open(input_file_path, 'r') as f:
        data = f.read().splitlines()

    state = set()
    for x, line in enumerate(data):
        for y, char in enumerate(line):
            if char == '#':
                state.add((x, y))

    p1, p2 = 0, 0
    proposals = defaultdict(list)

    for t in range(0, 10000):
        proposals = defaultdict(list)
        for x, y in state:
            ns = [
                (x - 1, y - 1), (x - 1, y), (x - 1, y + 1),
                (x, y - 1),                 (x, y + 1),
                (x + 1, y - 1), (x + 1, y), (x + 1, y + 1),
            ]

            if all(pos not in state for pos in ns):
                continue

            props = [
                (ns[0] not in state and ns[1] not in state and ns[2] not in state, (x - 1, y)),
                (ns[5] not in state and ns[6] not in state and ns[7] not in state, (x + 1, y)),
                (ns[0] not in state and ns[3] not in state and ns[5] not in state, (x, y - 1)),
                (ns[2] not in state and ns[4] not in state and ns[7] not in state, (x, y + 1)),
            ]

            for i in range(4):
                free, pos = props[(t + i) % 4]
                if free:
                    proposals[pos].append((x, y))
                    break

        moved = False 

        for pos, props in proposals.items():
            if len(props) == 1:
                moved = True
                state.remove(props[0])
                state.add(pos)

        if not moved:
            p2 = t + 1
            break

        if t == 9:
            min_x, max_x = min(x for x, _ in state), max(x for x, _ in state)
            min_y, max_y = min(y for _, y in state), max(y for _, y in state)
            p1 = sum(1 for p in ((x, y) for x in range(min_x, max_x + 1) for y in range(min_y, max_y + 1) if (x, y) not in state))

    print(f"Part 1: {p1}")
    print(f"Part 2: {p2}")

