import os

def main(input_dir):
    input_file_path = os.path.join(os.path.dirname(__file__), "../" + input_dir +"/04.in")
        
    with open(input_file_path, 'r') as f:
        data = f.read().splitlines()

    # Process the data
    # --> Turns each line into a list of sets containing the tasks of each elf
    assignment_pairs = []
    for pairs in data:
        this_pair = pairs.split(',')
        assigments = []
        for tasks in this_pair:
            start, end = list(map(int, tasks.split("-")))
            assigments.append(set(range(start, end+1)))

        assignment_pairs.append(assigments)

    includes_count = sum(
            1 for tasks_1, tasks_2 in assignment_pairs
            if tasks_1 == tasks_2 or tasks_1 < tasks_2 or tasks_2 < tasks_1
    )

    print(f"Part 1: Number of assignment inclusions = {includes_count}")

    overlap_count = sum(
            1 for tasks_1, tasks_2 in assignment_pairs
            if tasks_1 & tasks_2
    )

    print(f"Part 2: Numnber of assignment overlaps = {overlap_count}")
