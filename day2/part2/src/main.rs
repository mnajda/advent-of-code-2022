use std::env;
use std::fs;

fn load_file(path: &String) -> Vec<(char, char)> {
    let contents = fs::read_to_string(path).expect("Error reading file");
    contents
        .split("\n")
        .map(|row| row.split(' ').collect::<Vec<_>>())
        .map(|row| {
            (
                row[0].chars().next().unwrap(),
                row[1].chars().next().unwrap(),
            )
        })
        .collect()
}

fn solve(input: Vec<(char, char)>) -> i64 {
    input
        .iter()
        .map(|round| {
            let round_score = match round {
                ('A', 'Z') | ('B', 'Z') | ('C', 'Z') => 6,
                ('A', 'Y') | ('B', 'Y') | ('C', 'Y') => 3,
                ('A', 'X') | ('B', 'X') | ('C', 'X') => 0,
                _ => unreachable!(),
            };

            let shape_score = match (round.0, round_score) {
                ('A', 0) | ('B', 6) | ('C', 3) => 3,
                ('A', 6) | ('B', 3) | ('C', 0) => 2,
                ('A', 3) | ('B', 0) | ('C', 6) => 1,
                _ => unreachable!(),
            };

            shape_score + round_score
        })
        .sum()
}

fn main() {
    let args: Vec<String> = env::args().collect();
    if args.len() < 2 {
        println!("No file provided");
        return;
    }

    let input = load_file(&args[1]);
    let result = solve(input);
    println!("{}", result);
}
