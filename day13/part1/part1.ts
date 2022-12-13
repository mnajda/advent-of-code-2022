/// <reference types="node" />

import { readFileSync } from 'fs';

function compareNumber(lhs: number, rhs: number) {
    if (lhs < rhs) {
        return 1;
    }
    else if (lhs == rhs) {
        return 0;
    }
    else {
        return -1;
    }
}

function compare(lhs: any, rhs: any) {
    if (lhs === rhs) {
        return 0;
    }

    if (Number.isInteger(lhs) && Number.isInteger(rhs)) {
        return compareNumber(lhs, rhs);
    }

    if (!Array.isArray(lhs)) {
        lhs = [lhs];
    }

    if (!Array.isArray(rhs)) {
        rhs = [rhs];
    }

    const size = Math.max(lhs.length, rhs.length);
    for (let index = 0; index < size; index++) {
        if (index == lhs.length) {
            return 1;
        }

        if (index == rhs.length) {
            return -1;
        }

        let result = compare(lhs[index], rhs[index]);

        if (result == 1 || result == -1) {
            return result;
        }
    }
}

let path = process.argv[2];
let result =
    readFileSync(path, 'utf-8')
        .split('\n\n')
        .map((line, index): [number, number[]] => [index + 1, line.split("\n").map((elem) => JSON.parse(elem))])
        .filter((pair) => compare(pair[1][0], pair[1][1]) == 1)
        .reduce((acc, pair) => acc + pair[0], 0);

console.log(result)
