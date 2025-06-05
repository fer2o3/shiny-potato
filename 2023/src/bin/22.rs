use hashbrown::{HashMap, HashSet};
use itertools::Itertools;

fn fall(
    falling: &mut HashSet<usize>,
    above: &HashMap<usize, HashSet<usize>>,
    below: &HashMap<usize, HashSet<usize>>,
    i: usize,
) {
    if falling.insert(i) {
        if let Some(sup) = above.get(&i) {
            for &j in sup {
                if below[&j].iter().all(|x| falling.contains(x)) {
                    fall(falling, above, below, j);
                }
            }
        }
    }
}

#[aoc2023::main(22)]
fn main(input: &str) -> (usize, usize) {
    let mut bricks: Vec<_> = input
        .lines()
        .enumerate()
        .map(|(i, l)| {
            let (a, b) = l.split_once('~').unwrap();
            let parse = |s: &str| {
                s.split(',')
                    .map(|x| x.parse::<usize>().unwrap())
                    .collect_tuple()
                    .unwrap()
            };
            let (x1, y1, z1) = parse(a);
            let (x2, y2, z2) = parse(b);
            (x1, y1, z1, x2, y2, z2, i)
        })
        .collect();

    let mut grid = HashMap::new();
    for &(x1, y1, z1, x2, y2, z2, i) in &bricks {
        for (x, y, z) in (x1..=x2)
            .cartesian_product(y1..=y2)
            .cartesian_product(z1..=z2)
            .map(|((x, y), z)| (x, y, z))
        {
            grid.insert((x, y, z), i);
        }
    }

    while bricks.iter_mut().any(|b| {
        let (x1, y1, z1, x2, y2, z2, i) = *b;
        if z1 > 1
            && !(x1..=x2)
                .cartesian_product(y1..=y2)
                .any(|(x, y)| grid.contains_key(&(x, y, z1 - 1)))
        {
            *b = (x1, y1, z1 - 1, x2, y2, z2 - 1, i);
            for (x, y) in (x1..=x2).cartesian_product(y1..=y2) {
                grid.remove(&(x, y, z2));
                grid.insert((x, y, z1 - 1), i);
            }
            true
        } else {
            false
        }
    }) {}

    let (mut above, mut below) = (HashMap::new(), HashMap::new());
    for &(x1, y1, z1, x2, y2, _, i) in &bricks {
        for (x, y) in (x1..=x2).cartesian_product(y1..=y2) {
            if let Some(&j) = grid.get(&(x, y, z1 - 1)) {
                above.entry(j).or_insert_with(HashSet::new).insert(i);
                below.entry(i).or_insert_with(HashSet::new).insert(j);
            }
        }
    }

    let (mut p1, mut p2) = (0, 0);
    for i in 0..bricks.len() {
        let mut falling = HashSet::new();
        fall(&mut falling, &above, &below, i);
        if falling.len() == 1 {
            p1 += 1;
        }
        p2 += falling.len() - 1;
    }
    (p1, p2)
}
