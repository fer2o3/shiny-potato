import ast
import os

class Packet:
    """Packet is made up of a value which is either a list or an int.
    If it is a list it can contain other lists.
    It can be compared, and therefore sorted.
    """
    def __init__(self, value):
        self.value = value

    def __lt__(self, other):
        if isinstance(self.value, int) and isinstance(other.value, int):
            return self.value < other.value

        if isinstance(self.value, int) and isinstance(other.value, list):
            return Packet([self.value]) < other

        if isinstance(self.value, list) and isinstance(other.value, int):
            return self < Packet([other.value])

        if isinstance(self.value, list) and isinstance(other.value, list):
            for l, r in zip(self.value, other.value):
                if l != r:
                    return Packet(l) < Packet(r)

            return len(self.value) <= len(other.value)

def parse(line):
    left, right = line.splitlines()
    left = ast.literal_eval(left)
    right = ast.literal_eval(right)
    return left, right

def get_packets(data):
    return [Packet(ast.literal_eval(line)) for line in data.splitlines() if line]

def main(input_dir):
    input_file_path = os.path.join(os.path.dirname(__file__), "../" + input_dir +"/13.in")
    
    with open(input_file_path, 'r') as f:
        data = f.read()
        all_packets = get_packets(data)
        data = [parse(line) for line in data.split("\n\n")]

    ordered_pairs_sum = 0
    for i, packet in enumerate(data, start=1):
        left, right = packet
        if Packet(left) < Packet(right):
            ordered_pairs_sum += i

    print(f"Part 1: {ordered_pairs_sum}")

    div1 = Packet([[2]])
    div2 = Packet([[6]])

    all_packets.extend([div1, div2])

    sorted_packets = sorted(all_packets)
    i1, i2 = sorted_packets.index(div1) + 1, sorted_packets.index(div2) + 1

    print(f"Part 2: {i1 * i2}")
