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
            let shape_score = match round.1 {
                'Z' => 3,
                'Y' => 2,
                'X' => 1,
                _ => unreachable!(),
            };

            let round_score = match round {
                ('A', 'Y') | ('B', 'Z') | ('C', 'X') => 6,
                ('A', 'X') | ('B', 'Y') | ('C', 'Z') => 3,
                ('A', 'Z') | ('B', 'X') | ('C', 'Y') => 0,
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
