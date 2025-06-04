import os

ROCKS = [
        [(0,0), (0,1), (0,2), (0,3)],
        [(1,0), (0,1), (1,1), (1,2), (2,1)],
        [(0,0), (0,1), (0,2), (1,2), (2,2)],
        [(0,0), (1,0), (2,0), (3,0)],
        [(0,0), (0,1), (1,0), (1,1)]
]

# Returns the height of the tower of rocks
def get_height(cave):
    return cave.index(['.'] * 7)

def can_fit(cave, rock, h, w):
    return all(0 <= w + dw < 7 and cave[h+dh][w+dw] != '#' for dh, dw in rock)

def print_status(cave, height):
    cave_out = cave[::-1]
    for row in cave_out[-height:]:
        print(row)

# returns the 'index' of the highest piece of rock in each collumn
def col_height(cave):
    height = get_height(cave)
    def h(i):
        return next((x for x in range(height) if cave[height - x][i] == '#'), float('inf'))
    return (h(0), h(1), h(2), h(3), h(4), h(5), h(6))

def main(input_dir):
    input_file_path = os.path.join(os.path.dirname(__file__), "../" + input_dir +"/17.in")
    
    with open(input_file_path, 'r') as f:
         moves = [move for move in f.read().replace('\n', '')]

    total_height = 0
    
    length = len(moves)
    cave = [['.' for _ in range(7)] for _ in range(10000)]
    i, t = 0, 0
    cache = {} # We use a dictionnary because we love the complexity
    
    # h = distance from floor, w = distance from left wall
    # i = which rock needs to fall, t = which direction should the rock go
    while i < 1000000000000:
        print(i)
        rock = ROCKS[i % 5]
        h = get_height(cave) + 3
        w = 2

        while True:
            move = moves[t % length]
            if move == '>':
                w += 1 if can_fit(cave, rock, h, w + 1) else 0
            else:
                w -= 1 if can_fit(cave, rock, h, w - 1) else 0
            t += 1
            if h == 0 or not can_fit(cave, rock, h-1, w):
                break
            h -= 1

        for dh, dw in rock:
            cave[h + dh][w + dw] = '#'

        key = (i % 5, t % length, col_height(cave))
        if key in cache:
            idx, height = cache[key]
            repeats = (1000000000000 - idx) // (i - idx) - 1
            i += (i - idx) * repeats
            total_height += (get_height(cave) - height) * repeats
        else:
            cache[key] = (i, get_height(cave))

        i+=1
        
    
    height_2022 = [height for key, (i, height) in cache.items() if i == 2021]
    print(f"Part 1: {height_2022[0]}")
    print(f"Part 2 : {get_height(cave) + total_height}")
