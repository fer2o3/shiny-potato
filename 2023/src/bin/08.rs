use hashbrown::HashMap;
use num_integer::lcm;

fn navigate<'a>(
    current: Vec<&'a str>,
    instructions: &Vec<char>,
    network: &HashMap<&'a str, (&'a str, &'a str)>,
    length: usize,
) -> usize {
    let mut result: usize = 1;

    for mut cur in current {
        let mut steps = 0;
        while !cur.ends_with('Z') {
            cur = match instructions[steps % length] {
                'L' => network.get(cur).unwrap().0,
                'R' => network.get(cur).unwrap().1,
                _ => unreachable!(),
            };
            steps += 1;
        }
        result = lcm(result, steps);
    }
    result
}

#[aoc2023::main(08)]
fn main(input: &str) -> (usize, usize) {
    let (instructions, rest) = input.split_once("\n\n").unwrap();

    let instructions = instructions.chars().collect::<Vec<_>>();

    let mut network: HashMap<&str, (&str, &str)> = HashMap::new();

    for node in rest.lines() {
        let (src, dest) = node.split_once(" = ").unwrap();
        let dest = dest
            .trim_matches(|c| c == '(' || c == ')')
            .split_once(", ")
            .unwrap();
        network.insert(src, dest);
    }
    let length = instructions.len();

    let mut current: Vec<&str> = vec!["AAA"];
    let p1 = navigate(current, &instructions, &network, length);
    current = network
        .keys()
        .filter(|&&key| key.ends_with('A'))
        .map(|&key| key)
        .collect();
    let p2 = navigate(current, &instructions, &network, length);
    (p1, p2)
}
