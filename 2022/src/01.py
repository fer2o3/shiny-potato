import os

def main(input_dir):
    input_file_path = os.path.join(os.path.dirname(__file__), "../" + input_dir +"/01.in")
        
    with open(input_file_path, 'r') as f:
        elf_meals = f.read().split("\n\n")

    elf_calories = []
    for elf in elf_meals:
        calories = sum(map(int, elf.splitlines()))
        elf_calories.append(calories)

    print(f"Part 1: {max(elf_calories)}")
    elf_calories = sorted(elf_calories)
    print(f"Part 2: {sum(elf_calories[-3:])}")
