function getVerticalScore(row, col, input, count)
    if row <= 1 || col <= 1 || row >= length(input) || col >= length(input)
        return 0
    end

    result = 0
    height = input[row][col]

    while row > 1 && row < length(input)
        result += 1
        row += count
        if height <= input[row][col]
            return result
        end
    end

    return result
end

function getHorizontalScore(row, col, input, count)
    if row <= 1 || col <= 1 || row >= length(input) || col >= length(input)
        return 0
    end

    result = 0
    height = input[row][col]

    while col > 1 && col < length(input)
        result += 1
        col += count
        if height <= input[row][col]
            return result
        end
    end

    return result
end

function getScore(row, col, input)
    right = getVerticalScore(row, col, input, 1)
    left = getVerticalScore(row, col, input, -1)
    up = getHorizontalScore(row, col, input, 1)
    down = getHorizontalScore(row, col, input, -1)

    return left * right * up * down
end

function solve(input)
    highest_score = 0
    visible_count = (4 * (length(input) - 2)) + 4

    for row = 1:length(input)
        for col = 1:length(input[row])
            highest_score = max(highest_score, getScore(row, col, input)) 
        end
    end

    return highest_score
end

function main(args)
    input = map(line -> [parse(Int64, c) for c in collect(line)], readlines(args[1]))

    result = solve(input)
    @show result
end

main(ARGS)
