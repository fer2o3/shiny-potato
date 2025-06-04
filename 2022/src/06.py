import os

def main(input_dir):
    input_file_path = os.path.join(os.path.dirname(__file__), "../" + input_dir +"/06.in")
    
    with open(input_file_path, 'r') as f:
        data = f.read()

    stream_1, index_1 = process_stream(data, 4)
    stream_2, index_2 = process_stream(data, 14)

    print(f"Part 1: {index_1}")
    print(f"Part 2: {index_2}")


def process_stream(data: str, distinct_chars: int) -> tuple:
    stream = [char for char in data[:distinct_chars]]

    for i, char in enumerate(data[distinct_chars:], start=distinct_chars):
        if len(set(stream)) == distinct_chars: # If all chars are different
            break

        stream.pop(0)
        stream.append(char)

    return stream, i
