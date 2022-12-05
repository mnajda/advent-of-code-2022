package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

func MakeStack(raw_stacks []string) (stacks [][]byte) {
	num_of_stacks := int(raw_stacks[len(raw_stacks)-1][len(raw_stacks[len(raw_stacks)-1])-2] - '0')
	stacks = make([][]byte, num_of_stacks)

	for i := range raw_stacks[:len(raw_stacks)-1] {
		stack := raw_stacks[i]

		stack_number := 0
		for k := 1; k < len(stack); k += 4 {
			if stack[k] == ' ' {
				stack_number++
				continue
			}

			stacks[stack_number] = append(stacks[stack_number], stack[k])
			stack_number++
		}
	}

	return
}

func MakeInstructions(raw_instructions []string) (instructions [][]int) {
	instructions = make([][]int, len(raw_instructions))

	for i := range raw_instructions {
		raw_instruction := strings.Split(raw_instructions[i], " ")

		for k := range raw_instruction {
			if num, err := strconv.Atoi(raw_instruction[k]); err == nil {
				instructions[i] = append(instructions[i], num)
			}
		}
	}

	return
}

func Load(path string) (stacks [][]byte, instructions [][]int) {
	file, _ := os.Open(path)
	defer file.Close()

	scanner := bufio.NewScanner(file)
	raw_stacks := make([]string, 0)
	raw_instructions := make([]string, 0)

	for scanner.Scan() {
		if scanner.Text() == "" {
			break
		}

		raw_stacks = append(raw_stacks, scanner.Text())
	}

	for scanner.Scan() {
		line := strings.TrimSpace(scanner.Text())
		raw_instructions = append(raw_instructions, line)
	}

	stacks = MakeStack(raw_stacks)
	instructions = MakeInstructions(raw_instructions)

	return
}

func main() {
	path := os.Args[1]

	stacks, instructions := Load(path)

	for i := range instructions {
		instruction := instructions[i]

		how_many := instruction[0]
		from := instruction[1] - 1
		to := instruction[2] - 1

		to_move := stacks[from][:how_many]

		for k := len(to_move) - 1; k >= 0; k-- {
			stacks[to] = append([]byte{to_move[k]}, stacks[to]...)
		}

		stacks[from] = stacks[from][how_many:]
	}

	result := make([]byte, 0)
	for i := range stacks {
		result = append(result, stacks[i][0])
	}

	fmt.Println(string(result))
}
