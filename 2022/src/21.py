import os
from tqdm import tqdm

class Monkey():
    def __init__(self, m1, op='', m2=''):
        self.m1 = m1
        self.op = op
        self.m2 = m2

op_map = {
    '+': lambda x, y: x + y,
    '-': lambda x, y: x - y,
    '*': lambda x, y: x * y,
    '/': lambda x, y: x / y if y != 0 else None  
}

def get_val(m, monkeys):
    if isinstance(m.m1, int):
        return m.m1
    else:
        return op_map[m.op](get_val(monkeys[m.m1], monkeys), get_val(monkeys[m.m2], monkeys))


def main(input_dir):
    input_file_path = os.path.join(os.path.dirname(__file__), "../" + input_dir +"/21.in")
    
    with open(input_file_path, 'r') as f:
        data = f.read().splitlines()

    monkeys = {}
    for line in data:
        name, rest = line.split(':')
        val = rest.split()
        if len(val) == 1:
            monkeys[name] = Monkey(int(val[0]))
        else:
            monkeys[name] = Monkey(val[0], val[1], val[2])

    root_yells = int(get_val(monkeys['root'], monkeys))
    print(f"Part 1: {root_yells}")

    monkeys['root'].op = '-'
    res = None
    low, high = 0, 1e16
    while low < high:
        mid = int( low + (high - low) // 2)
        monkeys["humn"] = Monkey(mid)
        root_yells = get_val(monkeys['root'], monkeys)
        if root_yells == 0:
            break
        elif root_yells > 0:
            low = mid
        else:
            high = mid
    print(f"Part 2: {mid}")

