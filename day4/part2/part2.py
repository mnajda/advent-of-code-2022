import sys


class Assignment():
    def __init__(self, section):
        self.start = int(section[0])
        self.end = int(section[1])

    def does_overlap(self, other):
        return self.end >= other.start and self.start <= other.end


def create_assignments(pairs):
    return (Assignment(pairs[0].split("-")), Assignment(pairs[1].split("-")))


def load(path):
    with open(path, 'r') as file:
        contents = file.read().split("\n")
        assignment_pairs = list(
            map(lambda line: create_assignments(line.split(",")), contents))
        return assignment_pairs


def solve(assigment_pairs):
    return sum(map(lambda pair: pair[0].does_overlap(pair[1]) or pair[1].does_overlap(pair[0]), assigment_pairs))


def main():
    path = sys.argv[1]
    input = load(path)
    result = solve(input)
    print(result)


if __name__ == "__main__":
    main()
