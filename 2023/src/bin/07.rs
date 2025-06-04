use itertools::Itertools;
use std::cmp::Ordering;

fn card_label_rankings(label: char, joker: bool) -> usize {
    match label {
        'A' => 13,
        'K' => 12,
        'Q' => 11,
        'J' if joker => 0,
        'J' => 10,
        'T' => 9,
        '9' => 8,
        '8' => 7,
        '7' => 6,
        '6' => 5,
        '5' => 4,
        '4' => 3,
        '3' => 2,
        '2' => 1,
        _ => 0,
    }
}

fn get_hand_type(cards: &str, joker: bool) -> usize {
    let card_counts: Vec<usize> = cards
        .chars()
        .counts()
        .iter()
        .filter(|&(c, _)| !joker || *c != 'J')
        .map(|(_, count)| *count)
        .collect();

    let jokers = if joker {
        cards.chars().filter(|&c| c == 'J').count()
    } else {
        0
    };

    match *card_counts.iter().max().unwrap_or(&0) {
        count if count + jokers == 5 => 6,
        count if count + jokers == 4 => 5,
        3 if jokers == 0 && card_counts.contains(&2) => 4,
        3 => 3,
        2 => {
            let pairs_of_twos = card_counts.iter().filter(|&&v| v == 2).count();
            match pairs_of_twos {
                2 if jokers == 1 => 4,
                1 if jokers == 1 => 3,
                2 => 2,
                _ => 1,
            }
        }
        1 if jokers == 2 => 3,
        1 if jokers == 1 => 1,
        _ => 0,
    }
}

fn compare_hands(hand1: &str, hand2: &str, joker: bool) -> Ordering {
    match get_hand_type(hand1, joker).cmp(&get_hand_type(hand2, joker)) {
        Ordering::Equal => hand1
            .chars()
            .zip(hand2.chars())
            .find_map(|(c1, c2)| {
                match card_label_rankings(c1, joker).cmp(&card_label_rankings(c2, joker)) {
                    Ordering::Equal => None,
                    order => Some(order),
                }
            })
            .unwrap(),
        order => order,
    }
}

#[aoc2023::main(07)]
fn main(input: &str) -> (usize, usize) {
    let mut hands: Vec<(&str, usize)> = input
        .lines()
        .map(|line| {
            let (cards, bid) = line.split_once(' ').unwrap();
            (cards, bid.parse().unwrap())
        })
        .collect();

    hands.sort_by(|hand1, hand2| compare_hands(hand1.0, hand2.0, false));
    let p1: usize = hands
        .iter()
        .enumerate()
        .map(|(rank, (_, bid))| (rank + 1) * bid)
        .sum();

    hands.sort_by(|hand1, hand2| compare_hands(hand1.0, hand2.0, true));
    let p2: usize = hands
        .iter()
        .enumerate()
        .map(|(rank, (_, bid))| (rank + 1) * bid)
        .sum();

    (p1, p2)
}
