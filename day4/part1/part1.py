import sys


class Assignment():
    def __init__(self, section):
        self.start = int(section[0])
        self.end = int(section[1])

    def does_fully_contain(self, other):
        return self.start >= other.start and self.end <= other.end


def create_assignments(pairs):
    return (Assignment(pairs[0].split("-")), Assignment(pairs[1].split("-")))


def load(path):
    with open(path, 'r') as file:
        contents = file.read().split("\n")
        assignment_pairs = list(
            map(lambda line: create_assignments(line.split(",")), contents))
        return assignment_pairs


def solve(assigment_pairs):
    return sum(map(lambda pair: pair[0].does_fully_contain(pair[1]) or pair[1].does_fully_contain(pair[0]), assigment_pairs))


def main():
    path = sys.argv[1]
    input = load(path)
    result = solve(input)
    print(result)


if __name__ == "__main__":
    main()
