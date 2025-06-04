use hashbrown::HashMap;

fn run_hash(s: &str) -> usize {
    let mut hash: usize = 0;
    for c in s.chars() {
        hash += (c as u8) as usize;
        hash *= 17;
        hash %= 256;
    }
    hash
}

#[aoc2023::main(15)]
fn main(input: &str) -> (usize, usize) {
    let log = input.split(',').collect::<Vec<&str>>();

    let p1 = log.iter().map(|s| run_hash(s)).sum();

    let mut boxes: HashMap<usize, Vec<(&str, usize)>> = HashMap::new();

    for step in log.iter() {
        match step.chars().last().unwrap() {
            '-' => {
                let label = &step[..step.len() - 1];
                if let Some(boite) = boxes.get_mut(&run_hash(label)) {
                    boite.retain(|&(l, _)| l != label);
                }
            }
            x if x.is_numeric() => {
                let (label, focal) = step.split_once('=').unwrap();

                let boite = boxes.entry(run_hash(label)).or_insert(vec![]);

                if let Some(index) = boite.iter().position(|&(l, _)| label == l) {
                    boite[index] = (label, focal.parse::<usize>().unwrap());
                } else {
                    boite.push((label, focal.parse::<usize>().unwrap()));
                };
            }
            _ => unreachable!(),
        }
    }

    let mut p2: usize = 0;
    for (box_num, lenses) in &boxes {
        p2 += lenses
            .iter()
            .enumerate()
            .map(|(index, (_, focal))| (index + 1) * focal * (box_num + 1))
            .sum::<usize>();
    }
    (p1, p2)
}
