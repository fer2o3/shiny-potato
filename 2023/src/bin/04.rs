use std::collections::HashMap;

#[aoc2023::main(04)]
fn main(input: &str) -> (usize, usize) {
    let mut p1: usize = 0;
    let mut cards: HashMap<usize, usize> = HashMap::new();

    for line in input.lines() {
        let (id, card_data) = line.trim_start_matches("Card ").split_once(": ").unwrap();
        let id: usize = id.trim().parse().unwrap();
        let card_count = *cards.entry(id).or_insert(1);
        let numbers: Vec<&str> = card_data.split('|').map(|nums| nums.trim()).collect();

        let winning_numbers: Vec<u32> = numbers[0]
            .split_whitespace()
            .map(|num| num.parse().unwrap())
            .collect();

        let my_winning_numbers_count = numbers[1]
            .split_whitespace()
            .filter(|&num| winning_numbers.contains(&num.parse().unwrap()))
            .count();

        if my_winning_numbers_count > 0 {
            p1 += 1 << (my_winning_numbers_count - 1);
        }

        for n_id in (id + 1)..(id + my_winning_numbers_count + 1) {
            let cur_card_count = cards.entry(n_id).or_insert(1);
            *cur_card_count += 1 * card_count;
        }
    }
    let p2 = cards.values().sum();
    (p1, p2)
}
