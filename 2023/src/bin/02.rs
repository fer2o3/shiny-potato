use std::collections::HashMap;

#[aoc2023::main(02)]
fn main(input: &str) -> (usize, usize) {
    let mut p1: usize = 0;
    let mut p2: usize = 0;

    for line in input.lines() {
        let (id, subsets) = line.trim_start_matches("Game ").split_once(": ").unwrap();
        let mut possible = true;
        let mut min_cubes: HashMap<&str, usize> = HashMap::new();

        for cube in subsets.split([';', ',']) {
            let (count, color) = cube.trim().split_once(' ').unwrap();
            let count: usize = count.parse().unwrap();
            let cur_min = min_cubes.entry(color).or_insert(count);
            *cur_min = (*cur_min).max(count);

            match color {
                "red" if count > 12 => possible = false,
                "green" if count > 13 => possible = false,
                "blue" if count > 14 => possible = false,
                _ => (),
            }
        }
        if possible {
            p1 += id.parse::<usize>().unwrap()
        }
        p2 += min_cubes.values().product::<usize>();
    }
    (p1, p2)
}
