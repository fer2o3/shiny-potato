import re
import os

STACKS = [
            ['B', 'V', 'S', 'N', 'T', 'C', 'H', 'Q'],
            ['W', 'D', 'B', 'G'],
            ['F', 'W', 'R', 'T', 'S', 'Q', 'B'],
            ['L', 'G', 'W', 'S', 'Z', 'J', 'D', 'N'],
            ['M', 'P', 'D', 'V', 'F'],
            ['F', 'W', 'J'],
            ['L', 'N', 'Q', 'B', 'J', 'V'],
            ['G', 'T', 'R', 'C', 'J', 'Q', 'S', 'N'],
            ['J', 'S', 'Q', 'C', 'W', 'D', 'M']
        ]

def main(input_dir):
    input_file_path = os.path.join(os.path.dirname(__file__), "../" + input_dir +"/05.in")
    
    with open(input_file_path, 'r') as f:
        stack_data, instruction_data = f.read().split("\n\n")

    stacks = process_stack_data(stack_data.splitlines())
    moves = process_instruction_data(instruction_data.splitlines())

    # Part 1
    for count, src, dest in moves:
        for _ in range(count):
            stacks[dest].append(stacks[src].pop())

    result = "".join(stack[-1] for stack in stacks)
    print(f"Part 1: {result}")

    # Part 2
    for count, src, dest in moves:
        # Slice the items off the source stack and then move them to the dest stack
        STACKS[dest].extend(STACKS[src][-count:])
        STACKS[src][-count:] = [] # Delete the moved items

    result = "".join(stack[-1] for stack in STACKS)
    print(f"Part 2: {result}")




def process_instruction_data(data: list[str]) -> list[tuple[int, int, int]]:
    p = re.compile(r"move (\d+) from (\d+) to (\d+)") # regex are the best invention on earth
    moves = []
    for instruction in data:
        count, src, dest = list(map(int, p.findall(instruction)[0])) # Assign the capture group to their respective variable
        # We need the source and destination to be 0 indexed
        src -= 1
        dest -= 1
        moves.append((count, src, dest))

    return moves

def process_stack_data(data: list[str]) -> list[list]:
    p = re.compile(r"[A-Z]") # Create regular expression

    data = data[::-1] # Reverse the data in order to have the stack numbers first
    num_stacks = len(data[0].split())

    stacks = [[] for _ in range(num_stacks)] # create empty list for each stack

    # Process the stacks
    for stack in data[1:]: # Skip the stack numbers
        for stack_index in range(num_stacks):
            match = p.search(stack[4 * stack_index: 4 * (stack_index+1)]) # Width of stack is 4 --> "[N] "
            if match:
                stacks[stack_index].append(match.group())

    return stacks
