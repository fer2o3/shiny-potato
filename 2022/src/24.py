import os
from collections import deque, defaultdict

SIGNS = ['>', '<', 'v', '^']

def move_blizzard(blizzard, board):
    match blizzard:
        case (x, y, '>'):
            n_x, n_y = (x, y+1) if board[x][y+1] != "#" else (x, 1)
        case (x, y, 'v'):
            n_x, n_y = (x+1, y) if board[x+1][y] != "#" else (1, y)
        case (x, y, '^'):
            n_x, n_y = (x-1, y) if board[x-1][y] != "#" else (len(board) - 2, y)
        case (x, y, '<'):
            n_x, n_y = (x, y-1) if board[x][y-1] != "#" else (x, len(board[0]) - 2)

    return n_x, n_y, blizzard[2]

def update_blizzards(blizzards, board):
    new_blizzards = defaultdict(list)
    for (i, j), signs in blizzards.items():
        for sign in signs:
            nx, ny, sign = move_blizzard((i, j, sign), board)
            new_blizzards[(nx, ny)].append(sign)
    return new_blizzards

def run(blizzards, start, goal, board): 
    rows, cols = len(board), len(board[0])
    minutes = -1
    queue = deque([start])
    memory = set()

    while queue:
        x, y, minute = queue.popleft()

        if (x, y) == goal:
            break
        
        if minute > minutes:
            blizzards = update_blizzards(blizzards, board)
            minutes = minute

        for dx, dy in [(0, -1), (-1, 0), (0, 1), (1, 0), (0,0)]:
            nx, ny = x + dx, y + dy

            if (nx, ny, minute + 1) in memory:
                continue

            if len(blizzards[(nx, ny)]) > 0:
                continue

            if (1 <= nx < rows - 1 and 1 <= ny < cols - 1) or (nx, ny) == goal or (nx, ny) == (start[0], start[1]):
                memory.add((nx, ny, minute + 1))
                queue.append((nx, ny, minute + 1))

    return minutes, blizzards



def main(input_dir):
    input_file_path = os.path.join(os.path.dirname(__file__), "../" + input_dir +"/24.in")
    
    with open(input_file_path, 'r') as f:
        data = [[char for char in lines] for lines in f.read().splitlines()]

    blizzards = defaultdict(list)
    for i, line in enumerate(data):
        for j, char in enumerate(line):
            if char in SIGNS : blizzards[(i,j)].append(char)

    rows, cols = len(data), len(data[0])
    minutes1, blizzards = run(blizzards, (0,1,0), (rows-1, cols - 2), data)
    print(f"Part 1: {minutes1}")
    minutes2, blizzards = run(blizzards, (rows-1, cols - 2, 1), (0,1), data)
    minutes3, blizzards = run(blizzards, (0,1,1), (rows-1, cols - 2), data)
    print(f"Part 2: {minutes1 + minutes2 + minutes3}") 
