from dataclasses import dataclass
import os

@dataclass(frozen=True)
class Coord():
    x: int
    y: int

def get_rocks(data: list[str]) -> set[Coord]:
    rocks = set()
    for rock_lines in data:
        """ Transform data that looks like : 498,4 -> 498,6
            Into data that looks like : [Coord(498,4), Coord(498,6)]"""
        points = rock_lines.split(" -> ")
        raw_rock_lines = [raw.split(",") for raw in points]
        rock_lines = [Coord(int(x), int(y)) for x, y in raw_rock_lines]

        for i in range(len(rock_lines)-1):
            s_x, e_x = sorted((rock_lines[i].x, rock_lines[i+1].x))
            s_y, e_y = sorted((rock_lines[i].y, rock_lines[i+1].y))
            if s_x == e_x:
                for y in range(s_y, e_y + 1):
                    rocks.add(Coord(s_x, y))
            else:
                for x in range(s_x, e_x + 1):
                    rocks.add(Coord(x, s_y))

    return rocks

class Cave():

    VECTORS = [Coord(0,1), Coord(-1,1), Coord(1, 1)]

    def __init__(self, rocks):
        self.occupied = [[False] * 1000 for _ in range(1000)]
        for rock in rocks :
            self.occupied[rock.x][rock.y] = True

        self.max_y = max(rock.y for rock in rocks)
        self.floor = self.max_y + 2

    def in_void(self, unit: Coord):
        return not (0 <= unit.y <= self.max_y + 2)


    def drop_sand(self, floor=False):
        s = Coord(500, 0)
        falling = True
        while falling:
            if self.in_void(s):
                return False
            for v in self.VECTORS:
                candidate = Coord(s.x + v.x, s.y + v.y)
                if not self.occupied[candidate.x][candidate.y]:
                    if floor and candidate.y == self.floor:
                        falling = False
                        break
                    s = candidate
                    break
            else:
                falling = False

        self.occupied[s.x][s.y] = True
        return True

def main(input_dir):
    input_file_path = os.path.join(os.path.dirname(__file__), "../" + input_dir +"/14.in")
    
    with open(input_file_path, 'r') as f:
        data = f.read().splitlines()

    rocks = get_rocks(data)
    cave = Cave(rocks)
    units = 0
    while(cave.drop_sand()):
        units += 1
    print(f"Part 1: {units}")
    while(cave.occupied[500][0] == False):
        cave.drop_sand(True)
        units += 1
    print(f"Part 2: {units}")
