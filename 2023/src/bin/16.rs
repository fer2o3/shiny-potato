use hashbrown::HashSet;

fn radical_beam(
    beam: (i32, i32),
    energized: &mut HashSet<((i32, i32), (i32, i32))>,
    direction: (i32, i32),
    grid: &Vec<&[u8]>,
) {
    let mut stack = vec![(beam, direction)];

    while let Some(((r, c), direction)) = stack.pop() {
        if r < 0
            || r >= grid.len() as i32
            || c < 0
            || c >= grid[0].len() as i32
            || energized.contains(&((r, c), direction))
        {
            continue;
        }

        let (dr, dc) = direction;

        energized.insert(((r, c), direction));

        match grid[r as usize][c as usize] {
            b'|' if dc != 0 => {
                stack.push(((r - 1, c), (-1, 0)));
                stack.push(((r + 1, c), (1, 0)));
            }
            b'-' if dr != 0 => {
                stack.push(((r, c - 1), (0, -1)));
                stack.push(((r, c + 1), (0, 1)));
            }
            b'\\' => match (dr, dc) {
                (1, 0) => stack.push(((r, c + 1), (0, 1))),
                (-1, 0) => stack.push(((r, c - 1), (0, -1))),
                (0, 1) => stack.push(((r + 1, c), (1, 0))),
                (0, -1) => stack.push(((r - 1, c), (-1, 0))),
                _ => unreachable!(),
            },
            b'/' => match (dr, dc) {
                (1, 0) => stack.push(((r, c - 1), (0, -1))),
                (-1, 0) => stack.push(((r, c + 1), (0, 1))),
                (0, 1) => stack.push(((r - 1, c), (-1, 0))),
                (0, -1) => stack.push(((r + 1, c), (1, 0))),
                _ => unreachable!(),
            },
            _ => {
                stack.push(((r + dr, c + dc), direction));
            }
        }
    }
}

fn get_start_values(grid: &[&[u8]]) -> Vec<((i32, i32), (i32, i32))> {
    let rows = grid.len() as i32;
    let cols = grid[0].len() as i32;

    let top_edge = (0..cols).map(|col| ((0, col), (1, 0)));
    let bottom_edge = (0..cols).map(|col| ((rows - 1, col), (-1, 0)));
    let left_edge = (0..rows).map(|row| ((row, 0), (0, 1)));
    let right_edge = (0..rows).map(|row| ((row, cols - 1), (0, -1)));

    top_edge
        .chain(bottom_edge)
        .chain(left_edge)
        .chain(right_edge)
        .collect()
}

#[aoc2023::main(16)]
fn main(input: &str) -> (usize, usize) {
    let grid = input.lines().map(|l| l.as_bytes()).collect::<Vec<_>>();

    // Part 1
    let mut energized: HashSet<((i32, i32), (i32, i32))> = HashSet::new();
    radical_beam((0, 0), &mut energized, (0, 1), &grid);
    let mut uniq_energized = HashSet::new();
    for (coord, _) in &energized {
        uniq_energized.insert(coord);
    }
    let p1 = uniq_energized.len();

    // Part 2
    let mut p2 = 0;
    for (start, direction) in get_start_values(&grid) {
        let mut energized = HashSet::new();
        radical_beam(start, &mut energized, direction, &grid);
        let uniq_energized: HashSet<_> = energized.iter().map(|(coord, _)| *coord).collect();
        p2 = p2.max(uniq_energized.len());
    }

    (p1, p2)
}
