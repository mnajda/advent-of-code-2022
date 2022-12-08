function checkVertical(row, col, input, count)
    height = input[row][col]

    while row > 1 && row < length(input)
        row += count
        if height <= input[row][col]
            return false
        end
    end

    return true
end

function checkHorizontal(row, col, input, count)
    height = input[row][col]

    while col > 1 && col < length(input)
        col += count
        if height <= input[row][col]
            return false
        end
    end

    return true
end

function isVisible(row, col, input, checked)
    if checked[row][col]
        return false
    end

    visible = checkVertical(row, col, input, 1) || checkVertical(row, col, input, -1)
    visible = visible || checkHorizontal(row, col, input, 1) || checkHorizontal(row, col, input, -1)

    if visible
        checked[row][col] = true;
        return true;
    end

    return false
end

function solve(input)
    visible_count = (4 * (length(input) - 2)) + 4
    checked = [[false for i in 1:length(input)] for i in 1:length(input)]

    for row = 2:length(input)-1
        for col = 2:length(input[row])-1
            if isVisible(row, col, input, checked)
                visible_count += 1
            end
        end
    end

    visible_count
end

function main(args)
    input = map(line -> [parse(Int64, c) for c in collect(line)], readlines(args[1]))

    result = solve(input)
    @show result
end

main(ARGS)
