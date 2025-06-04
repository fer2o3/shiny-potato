const STRING_TO_DIGIT: &[&[u8]] = &[
    b"zero", b"one", b"two", b"three", b"four", b"five", b"six", b"seven", b"eight", b"nine",
];

fn digit_sum(line: &[u8], spelled: bool) -> usize {
    let mut digits = line.iter().enumerate().filter_map(|(i, &c)| {
        if c.is_ascii_digit() {
            Some((c - b'0') as usize)
        } else if spelled {
            STRING_TO_DIGIT
                .iter()
                .position(|&d| line[i..].starts_with(d))
        } else {
            None
        }
    });

    let a = digits.next().unwrap_or_default();
    let b = digits.last().unwrap_or(a);
    a * 10 + b
}

#[aoc2023::main(01)]
fn main(input: &str) -> (usize, usize) {
    let lines = input.lines().map(str::as_bytes).collect::<Vec<_>>();
    let p1 = lines.iter().map(|line| digit_sum(line, false)).sum();
    let p2 = lines.iter().map(|line| digit_sum(line, true)).sum();
    (p1, p2)
}
