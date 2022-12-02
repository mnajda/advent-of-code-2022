use std::env;
use std::fs;

fn load_file(path: &String) -> Vec<(char, char)> {
    let contents = fs::read_to_string(path).expect("Error reading file");
    contents
        .split("\n")
        .map(|row| row.split(' ').collect::<Vec<_>>())
        .map (|row| (row[0].chars().next().unwrap(), row[1].chars().next().unwrap()))
        .collect()
}

fn solve(input: Vec<(char, char)>) -> i64 {
    input.iter().map(
        |round| {
            match round {
                ('A', 'X') => 1 + 3,
                ('A', 'Y') => 2 + 6,
                ('A', 'Z') => 3 + 0,
                ('B', 'X') => 1 + 0,
                ('B', 'Y') => 2 + 3,
                ('B', 'Z') => 3 + 6,
                ('C', 'X') => 1 + 6,
                ('C', 'Y') => 2 + 0,
                ('C', 'Z') => 3 + 3,
                _ => unreachable!()
            }
        }).sum()
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
