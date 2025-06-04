import re
import os

class Monkey():
    def __init__(self, items, op, test):
        self.inspected = 0
        self.items = items
        self.op = op
        self.test = test

    def throw_item(self, relief=None) -> tuple[int, int]:
        if not self.items:
            return
        self.inspected += 1
        item = self.items.pop(0)
        if not relief:
            item = self.op(item) // 3
        else:
            item = self.op(item) % relief
        dest = self.test[1] if item % self.test[0] == 0 else self.test[2]
        return item, dest

def func_from_string(expression):
    def func(x):
        return eval(expression, {'old': x})

    return func

def parse(data: list[str]) -> list[Monkey]:
    monkeys = []
    for monkey in data:
        for line in monkey.splitlines():                
            if "items:" in line:
                items = list(map(int, re.findall(r"(\d+)", line)))

            if "Operation:" in line:
                expression = line.split("=")[-1].strip()
                op = func_from_string(expression)
            
            if "Test:" in line:
                test = int(re.findall(r"\d+", line)[0])
            
            if "true:" in line:
                monkey_true = int(re.findall(r"\d+", line)[0])
            
            if "false:" in line:
                monkey_false = int(re.findall(r"\d+", line)[0])

        monkeys.append(Monkey(items, op, (test, monkey_true, monkey_false)))

    return monkeys

def find_monkey_business(monkeys, rounds, relief=None):
    for _ in range(rounds):
        for monkey in monkeys:
            while monkey.items:
                item, dest = monkey.throw_item(relief)
                monkeys[dest].items.append(item)
    inspected = [monkey.inspected for monkey in monkeys]
    inspected = sorted(inspected)
    return inspected[-1] * inspected[-2]

def main(input_dir):
    input_file_path = os.path.join(os.path.dirname(__file__), "../" + input_dir +"/11.in")
    
    with open(input_file_path, 'r') as f:
        data = f.read().split("\n\n")

    # Part 1
    monkeys = parse(data)
    monkey_business1 = find_monkey_business(monkeys, 20)

    # Part 2:
    monkeys = parse(data)
    super_number = 1
    for number in [monkey.test[0] for monkey in monkeys]:
        super_number *= number
    monkey_business2 = find_monkey_business(monkeys, 10000, super_number)
    print(f"Part 1 : {monkey_business1}")
    print(f"Part 2 : {monkey_business2}")
