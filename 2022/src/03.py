import os

def main(input_dir):
    input_file_path = os.path.join(os.path.dirname(__file__), "../" + input_dir +"/03.in")
        
    with open(input_file_path, 'r') as f:
        data = f.read().splitlines()

    item_to_priority = {}
    for i, ordinal in enumerate(range(ord('a'), ord('z')+1), start = 1):
        item_to_priority[chr(ordinal)] = i
        item_to_priority[chr(ordinal + ord('A') - ord('a'))] = i + 26

    res = 0
    for rucksack in data:
        # Split the rucksack into two compartments
        # Turn them into sets to remove duplicates
        compartment_1 = set(rucksack[:len(rucksack)//2])
        compartment_2 = set(rucksack[len(rucksack)//2:])

        shared = compartment_1 & compartment_2 # Intersection

        for item in shared: # Necessary to access value
            res += item_to_priority[item]

    print(f"Part 1: Sum of priorities = {res}")

    res = 0
    for i in range(0, len(data), 3):
        group = data[i:i+3]

        shared = set(group[0]) & set(group[1]) & set(group[2])

        for item in shared:
            res += item_to_priority[item]

    print(f"Part 2: Sum of priorities = {res}")

