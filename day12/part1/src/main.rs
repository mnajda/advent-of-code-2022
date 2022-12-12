use std::collections::HashMap;
use std::collections::VecDeque;
use std::env;
use std::fs;
use std::hash::Hash;

type Point = (usize, usize);

#[derive(Debug, Hash, PartialEq, Eq, Clone, Copy)]
struct Position {
    point: Point,
    elevation: u8,
}

fn get_value(c: char) -> u8 {
    match c {
        'S' => 'a' as u8,
        'E' => 'z' as u8,
        _ => c as u8,
    }
}

fn load_file(path: &String) -> (Position, Position, Vec<Vec<Position>>) {
    let contents = fs::read_to_string(path).expect("Error reading file");

    let mut start = None;
    let mut end = None;
    let grid = contents
        .split("\n")
        .enumerate()
        .map(|(col, line)| {
            line.chars()
                .enumerate()
                .map(|(row, c)| {
                    if c == 'S' {
                        start = Some(Position {
                            point: (col, row),
                            elevation: get_value(c),
                        });
                    }
                    if c == 'E' {
                        end = Some(Position {
                            point: (col, row),
                            elevation: get_value(c),
                        });
                    }
                    Position {
                        point: (col, row),
                        elevation: get_value(c),
                    }
                })
                .collect()
        })
        .collect();

    (start.unwrap(), end.unwrap(), grid)
}

fn neighbourhood(position: &Point, grid: &Vec<Vec<Position>>) -> Vec<Point> {
    let mut neighbours = Vec::new();
    let (y, x) = *position;
    let (len_y, len_x) = (grid.len(), grid[0].len());

    if x > 0 {
        neighbours.push((y, x - 1));
    }
    if x < len_x - 1 {
        neighbours.push((y, x + 1));
    }
    if y > 0 {
        neighbours.push((y - 1, x));
    }
    if y < len_y - 1 {
        neighbours.push((y + 1, x));
    }

    neighbours
}

fn solve(input: (Position, Position, Vec<Vec<Position>>)) -> Option<i64> {
    let (start, end, grid) = input;

    let mut to_visit = VecDeque::from([(start, 0)]);
    let mut visited: HashMap<(usize, usize), bool> = HashMap::from_iter(
        grid.iter()
            .flatten()
            .map(|position| (position.point, false)),
    );
    visited.insert(start.point, true);

    while let Some((current, steps)) = to_visit.pop_front() {
        if current.point == end.point {
            return Some(steps);
        }

        for (y, x) in neighbourhood(&current.point, &grid) {
            if grid[y][x].elevation <= current.elevation + 1 && !visited[&(y, x)] {
                to_visit.push_back((grid[y][x], steps + 1));
                visited.insert(grid[y][x].point, true);
            }
        }
    }

    None
}

fn main() {
    let args: Vec<String> = env::args().collect();
    if args.len() < 2 {
        panic!("No file provided");
    }

    let input = load_file(&args[1]);

    let result = solve(input);
    println!("{}", result.unwrap());
}
