use std::collections::HashMap;

#[aoc2023::main(03)]
fn main(input: &str) -> (usize, usize) {
    let lines = input.split('\n').map(str::as_bytes).collect::<Vec<_>>();
    let mut symbols = HashMap::new();
    for (row, line) in lines.iter().enumerate() {
        let mut col = 0;
        while col < line.len() {
            let (start, mut symbol) = (col, None);
            while col < line.len() && line[col].is_ascii_digit() {
                for (dr, dc) in [
                    (0, 1),
                    (1, 1),
                    (1, 0),
                    (1, -1),
                    (0, -1),
                    (-1, -1),
                    (-1, 0),
                    (-1, 1),
                ] {
                    let (nr, nc) = ((row as i32 + dr) as usize, (col as i32 + dc) as usize);
                    let Some(&adjacent) = lines.get(nr).and_then(|l| l.get(nc)) else {
                        continue;
                    };
                    if !adjacent.is_ascii_digit() && adjacent != b'.' {
                        symbol = Some((nr, nc, adjacent as char));
                        break;
                    }
                }
                col += 1;
            }
            if start < col {
                if let Some(symbol) = symbol {
                    let num = line[start..col]
                        .iter()
                        .fold(0, |n, c| n * 10 + (c - b'0') as usize);
                    symbols.entry(symbol).or_insert(Vec::new()).push(num);
                }
            }
            col += 1;
        }
    }
    let p1 = symbols.values().flat_map(|v| v).sum();
    let p2 = symbols
        .iter()
        .filter(|(&(_, _, s), v)| s == '*' && v.len() == 2)
        .map(|(_, v)| v[0] * v[1])
        .sum();
    (p1, p2)
}
