import os


SCORES = {
        ('A', 'Y'): 8,
        ('B', 'Z'): 9,
        ('C', 'X'): 7,
        ('A', 'X'): 4,
        ('B', 'Y'): 5,
        ('C', 'Z'): 6,
        ('A', 'Z'): 3,
        ('B', 'X'): 1,
        ('C', 'Y'): 2,
    }

def main(input_dir):
    input_file_path = os.path.join(os.path.dirname(__file__), "../" + input_dir +"/02.in")
        
    with open(input_file_path, 'r') as f:
        data = f.read().splitlines()
    
    # Make a list of each rounds
    round1 = [(line[0], line[2]) for line in data]
    round2 = [
            ('A', 'Z') if a == 'A' and b == 'X' else
            ('B', 'X') if a == 'B' and b == 'X' else
            ('C', 'Y') if a == 'C' and b == 'X' else
            ('A', 'X') if a == 'A' and b == 'Y' else
            ('B', 'Y') if a == 'B' and b == 'Y' else
            ('C', 'Z') if a == 'C' and b == 'Y' else
            ('A', 'Y') if a == 'A' and b == 'Z' else
            ('B', 'Z') if a == 'B' and b == 'Z' else
            ('C', 'X') if a == 'C' and b == 'Z' else
            None for a, b in round1
            ]

    score1 = sum(SCORES[(a, b)] for a, b in round1) # Part 1
    print(f"Part 1: {score1}")
    score2 = sum(SCORES[(a, b)] for a, b in round2) # Part 2
    print(f"Part 2: {score2}")

