import os
import sets

proc first_marker(input: string): int =
    let start_index = 3
    for i in countup(start_index, input.len - 1):
        let distinct_occurences = toHashSet(input[i-start_index..i])
        if distinct_occurences.len == 4:
            return i + 1

    return 0


let filepath = paramStr(1)
let input = readFile(filepath)

let result = first_marker(input)

echo result