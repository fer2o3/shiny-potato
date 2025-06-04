fn next_history_val(data: Vec<i32>, mut dec_len: usize) -> i32 {
    let mut history: Vec<Vec<i32>> = vec![data];
    let mut inc_len = 1;

    while history.last().unwrap().iter().any(|i| *i != 0) {
        let mut new: Vec<i32> = Vec::new();
        for i in 1..dec_len {
            new.push(history[inc_len - 1][i] - history[inc_len - 1][i - 1])
        }
        history.push(new);
        dec_len -= 1;
        inc_len += 1;
    }
    history.iter().map(|list| *list.last().unwrap()).sum()
}

#[aoc2023::main(09)]
fn main(input: &str) -> (usize, usize) {
    let mut p1: i32 = 0;
    let mut p2: i32 = 0;
    for line in input.lines() {
        let data = line
            .split_whitespace()
            .map(|s| s.parse::<i32>().unwrap())
            .collect::<Vec<i32>>();

        let dec_len = data.len();
        let rev_data: Vec<i32> = data.iter().rev().cloned().collect();
        p1 += next_history_val(data, dec_len);
        p2 += next_history_val(rev_data, dec_len);
    }
    (p1 as usize, p2 as usize)
}
