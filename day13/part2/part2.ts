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

    return 0;
}

let path = process.argv[2];
let data =
    readFileSync(path, 'utf-8')
        .split('\n')
        .filter((line) => line != "")
        .map((line) => JSON.parse(line));

data.push(JSON.parse("[[2]]"));
data.push(JSON.parse("[[6]]"));

let result =
    data
    .sort((lhs, rhs) => compare(lhs, rhs))
    .reverse()
    .map((packet, index): [any[], number] => [packet, index + 1])
    .filter((packet) => JSON.stringify(packet[0]) == "[[2]]" || JSON.stringify(packet[0]) == "[[6]]")
    .reduce((acc, packet) => acc * packet[1], 1);

console.log(result);
