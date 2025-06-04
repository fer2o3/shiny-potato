use hashbrown::HashMap;
use itertools::Itertools;

fn get_combinations(
    pattern: &str,
    values: &Vec<usize>,
    count: usize,
    cache: &mut HashMap<(usize, usize, usize), usize>,
) -> usize {
    // If we are in a group of '#' even though they have all been found,
    // Then this combination is not valid
    if count > 0 && values.is_empty() {
        return 0;
    }

    if pattern.is_empty() {
        return match values.len() {
            // If we have no more groups of vents to add
            // and we are not in a group of '#',
            // then this combination is valid
            0 if count == 0 => 1,

            // If we have exactly one last group to add,
            // and we are in a group of '#',
            // and the number of '#' is the correct amount,
            // then this combination is valid
            1 if count == values[0] => 1,

            _ => 0,
        };
    }

    // If we've already been in this exact same position before,
    // We return the value we already found
    let key = (pattern.len(), count, values.len());
    if let Some(&res) = cache.get(&key) {
        return res;
    }

    let combinations = match pattern.chars().next().unwrap() {
        '.' if count > 0 && count != values[0] => 0,
        '.' if count > 0 => get_combinations(&pattern[1..], &values[1..].to_vec(), 0, cache),
        '.' => get_combinations(&pattern[1..], values, 0, cache),
        '#' if count > 0 => get_combinations(&pattern[1..], values, count + 1, cache),
        '#' => get_combinations(&pattern[1..], values, 1, cache),
        '?' if count > 0 => {
            let mut res = get_combinations(&pattern[1..], &values, count + 1, cache);
            if count == values[0] {
                res += get_combinations(&pattern[1..], &values[1..].to_vec(), 0, cache);
            }
            res
        }
        '?' => {
            get_combinations(&pattern[1..], values, 1, cache)
                + get_combinations(&pattern[1..], values, 0, cache)
        }
        _ => unreachable!(),
    };
    cache.insert(key, combinations);
    combinations
}

#[aoc2023::main(12)]
fn main(input: &str) -> (usize, usize) {
    let mut p1: usize = 0;
    let mut p2: usize = 0;
    let mut cache = HashMap::new();
    for line in input.lines() {
        let (pattern, rest) = line.split_once(' ').unwrap();
        let mut values = rest.split(',').map(|num| num.parse().unwrap()).collect();

        cache.clear();
        p1 += get_combinations(pattern, &values, 0, &mut cache);

        let pattern = (0..5).map(|_| pattern).join("?");
        values = (0..5).flat_map(|_| &values).copied().collect();
        cache.clear();
        p2 += get_combinations(&pattern, &values, 0, &mut cache);
    }
    (p1, p2)
}
