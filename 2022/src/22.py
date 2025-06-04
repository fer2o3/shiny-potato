import os
import re

DIRECTIONS = [(0, 1), (1, 0), (0, -1), (-1, 0)]

def wrap1(board, x, y, direction):
    dx, dy = DIRECTIONS[direction]
    while 0 <= x - dx < len(board) and 0 <= y - dy < len(board[x-dx]) and board[x - dx][y - dy] != ' ':
        x, y = x - dx, y - dy
    
    return (x, y, direction)

def wrap2(board, x, y, direction):
    cube_pos = (x//50, y//50, direction)
    match (x//50, y//50, direction):
        case (0,1,3): cube_pos = (3, 0, 0)
        case (0,1,2): cube_pos = (2, 0, 0)
        case (0,2,3): cube_pos = (3, 0, 3)
        case (0,2,0): cube_pos = (2, 1, 2)
        case (0,2,1): cube_pos = (1, 1, 2)
        case (1,1,0): cube_pos = (0, 2, 3)
        case (1,1,2): cube_pos = (2, 0, 1)
        case (2,0,3): cube_pos = (1, 1, 0)
        case (2,0,2): cube_pos = (0, 1, 0)
        case (2,1,0): cube_pos = (0, 2, 2)
        case (2,1,1): cube_pos = (3, 0, 2)
        case (3,0,0): cube_pos = (2, 1, 3)
        case (3,0,1): cube_pos = (0, 2, 1)
        case (3,0,2): cube_pos = (0, 1, 1)
        case (_,_,_): print(cube_pos)

    dx, dy = x % 50, y % 50
    index = [dx, 49 - dy, 49 - dx, dy][direction]
    nx, ny = [(index, 0), (0, 49 - index), (49 - index, 49), (49, index)][cube_pos[2]]

    return cube_pos[0] * 50 + nx, cube_pos[1] * 50 + ny, cube_pos[2]


def move(board, moves, wrap):
    x, y, direction = 0, board[0].index('.'), 0
    for move in moves:
        if isinstance(move, str):
            direction = (direction-1)%4 if move == 'L' else (direction+1)%4
        else:
            for _ in range(move):
                dx, dy = DIRECTIONS[direction]
                if 0 <= x + dx < len(board) and 0 <= y + dy < len(board[x+dx]):
                    pos = board[x+dx][y+dy]
                else:
                    pos = ' '

                if pos == '.':
                    x, y = x + dx, y + dy
                elif pos == '#':
                    break
                else:
                    nx, ny, new_direction = wrap(board, x, y, direction)
                    if board[nx][ny] == '#': break
                    x, y, direction = nx, ny, new_direction

    return 1000*(x+1) + 4*(y+1) + direction


def main(input_dir):
    input_file_path = os.path.join(os.path.dirname(__file__), "../" + input_dir +"/22.in")
    
    with open(input_file_path, 'r') as f:
        board, path_description = f.read().split('\n\n')

    # Parse input
    board_map = [[char for char in board] for board in board.splitlines()]
    matches = re.findall(r'(\d+|[A-Z])', path_description)
    path_description = [int(match) if match.isdigit() else match for match in matches]
 
    print(move(board_map, path_description, wrap1))
    print(move(board_map, path_description, wrap2))
    

