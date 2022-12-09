import sys
import math


def load(path):
    with open(path, 'r') as file:
        contents = file.read().split("\n")
        moves = [line.split(" ") for line in contents]
        return moves


def move_head(head, direction):
    if direction == "R": return (head[0], head[1] + 1)
    elif direction == "L": return (head[0], head[1] - 1)
    elif direction == "U": return (head[0] + 1, head[1])
    elif direction == "D": return (head[0] - 1, head[1])
    else: return ()


def move_vertical(tail, head):
    return head[0] - tail[0] == 0


def move_horizontal(tail, head):
    return head[1] - tail[1] == 0


def move_tail(tail, head):
    if tail == head:
        return tail
    
    if abs(head[0] - tail[0]) <= 1 and abs(tail[1] - head[1]) <= 1:
        return tail

    if move_vertical(tail, head):
        return (tail[0], math.ceil((head[1] - tail[1]) / 2) + tail[1])

    if move_horizontal(tail, head):
        return (math.ceil((head[0] - tail[0]) / 2) + tail[0], tail[1])

    if (head[0] > tail[0] and head[1] > tail[1]):
        return (tail[0] + 1, tail[1] + 1)

    if (head[0] > tail[0] and head[1] < tail[1]):
        return (tail[0] + 1, tail[1] - 1)

    if (head[0] < tail[0] and head[1] > tail[1]):
        return (tail[0] -1 , tail[1] + 1)

    if (head[0] < tail[0] and head[1] < tail[1]):
        return (tail[0] - 1, tail[1] - 1)


def solve(moves):
    head = (0, 0)
    tail = (0, 0)

    visited = {tail : True}

    for move in moves:
        direction, val = move

        for _ in range(0, int(val)):
            head = move_head(head, direction)
            tail = move_tail(tail, head)
            visited[tail] = True

    return len(visited)


def main():
    path = sys.argv[1]
    input = load(path)

    result = solve(input)
    print(result)


if __name__ == "__main__":
    main()
