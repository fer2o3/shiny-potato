fn shoelace(instructions: impl Iterator<Item = (u8, isize)>) -> isize {
    let (mut i, mut b, mut r, mut c) = (0, 0, 0, 0);
    for (direction, norm) in instructions {
        let (old_r, old_c) = (r, c);
        match direction {
            b'U' => r += norm,
            b'R' => c += norm,
            b'D' => r -= norm,
            b'L' => c -= norm,
            _ => unreachable!(),
        };
        i += (old_c + c) * (old_r - r) / 2;
        b += norm;
    }
    i + b / 2 + 1
}

#[aoc2023::main(18)]
fn main(input: &str) -> (isize, isize) {
    let p1 = input.lines().map(|l| {
        let (n, _) = l[2..].split_once(' ').unwrap();
        (l.as_bytes()[0], n.parse::<isize>().unwrap())
    });
    let p2 = input.split('\n').map(|l| {
        let (_, color) = l.split_once(" (#").unwrap();
        let d = match color.as_bytes()[color.len() - 2] {
            b'0' => b'R',
            b'1' => b'D',
            b'2' => b'L',
            b'3' => b'U',
            _ => unreachable!(),
        };
        (
            d,
            isize::from_str_radix(&color[0..color.len() - 2], 16).unwrap(),
        )
    });
    (shoelace(p1), shoelace(p2))
}
