from dataclasses import dataclass
import os

@dataclass(frozen=True)
class File:
    name: str
    size: int

class Directory:
    """Represents a file system directory. Has a parent directory,
    subdirectories or/and files.
    """
    def __init__(self, name: str, parent_dir=None):
        self.name = name
        self.parent_dir = parent_dir
        self.files = []
        self.directories = []

    def get_directory(self, name: str):
        return next(dir for dir in self.directories if dir.name == name)

    def get_all_dirs(self) -> list['Directory']:
        return [ 
            directory for subdir in self.directories
            for directory in (subdir.get_all_dirs() + [subdir])
        ]

    @property
    def size(self):
        return sum(file.size for file in self.files) + sum(
                directory.size for directory in self.directories
            )

    def add_file(self, file):
        self.files.append(file)

    def add_directory(self, directory):
        self.directories.append(directory)
        directory.parent_dir = self


def main(input_dir):
    input_file_path = os.path.join(os.path.dirname(__file__), "../" + input_dir +"/07.in")
    
    with open(input_file_path, 'r') as f:
        data = f.read().splitlines()

    root = parse(data)
    directories = root.get_all_dirs()

    small_directories = [d for d in directories if d.size <= 100000]
    print(f"Part 1: {sum(d.size for d in small_directories)}")

    current_size = 70000000 - root.size
    size_needed = 30000000 - current_size
    big_enough_dirs = [d for d in directories if d.size >= size_needed]
    smallest = min(big_enough_dirs, key=lambda x: x.size)
    print(f"Part 2: {smallest.size}")


def parse(data: list[str]) -> Directory:
    root = Directory("/")
    current = root

    for line in data:
        if line.startswith("$"):
            instruction = line.split()
            command = instruction[1]
            if command == "ls":
                continue
            if command == "cd":
                argument = instruction[2]
                if argument == "..":
                    current = current.parent_dir
                elif argument != '/':
                    current = current.get_directory(argument)
                else:
                    current = root
        else:
            element = line.split()
            if element[0] == "dir":
                directory = Directory(element[1])
                current.add_directory(directory)
            else:
                file = File(element[1], size=int(element[0]))
                current.add_file(file)

    return root 

