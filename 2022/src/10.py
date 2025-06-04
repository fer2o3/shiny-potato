import os

def main(input_dir):
    input_file_path = os.path.join(os.path.dirname(__file__), "../" + input_dir +"/10.in")
    
    with open(input_file_path, 'r') as f:
        data = f.read().splitlines()

    x, cycle, signal_strength, signal_render = 1, 0, 0, ""

    def tick():
        nonlocal cycle, signal_strength, signal_render
        if cycle % 40 == 0:
            signal_render += '\n'
        signal_render += '█' if abs(x - cycle % 40) < 2 else ' '
        cycle += 1
        if (cycle - 20) % 40 == 0:
            signal_strength += cycle * x

    for line in data:
        tick()
        if len(line) > 4:
            tick()
            x += int(line[5:])

    print(f"Part 1: {signal_strength}")
    print(f"Part 2: \n{signal_render}")
