fn count_winning_strats(times: &[usize], distances: &[usize]) -> usize {
    times
        .iter()
        .zip(distances)
        .map(|(&time, &dist)| {
            let delta: f64 = (time * time - 4 * dist) as f64;
            let x1 = (time as f64 - delta.sqrt()) / 2.0;
            let x2 = (time as f64 + delta.sqrt()) / 2.0;
            (x1.max(x2).floor() - x2.min(x1).ceil()) as usize + 1
        })
        .product()
}

#[aoc2023::main(06)]
fn main(input: &str) -> (usize, usize) {
    let mut time_vect1 = Vec::new();
    let mut dist_vect1 = Vec::new();
    let mut time_vect2 = Vec::new();
    let mut dist_vect2 = Vec::new();

    for line in input.lines() {
        let numbers: Vec<usize> = line
            .split_whitespace()
            .filter_map(|word| word.parse().ok())
            .collect();

        let number: String = line.chars().filter(|&c| c.is_numeric()).collect();

        if line.starts_with("Time:") {
            time_vect1 = numbers;
            time_vect2.push(number.parse().unwrap())
        } else {
            dist_vect1 = numbers;
            dist_vect2.push(number.parse().unwrap())
        }
    }

    let p1 = count_winning_strats(&time_vect1, &dist_vect1);
    let p2 = count_winning_strats(&time_vect2, &dist_vect2);

    (p1, p2)
}
