use hashbrown::HashMap;

fn p1(grid: &Vec<Vec<u8>>) -> usize {
    let mut load = 0;
    let length = grid.len();
    let mut counters = vec![0; grid[0].len()];
    for (row_i, row) in grid.iter().enumerate() {
        for (col_i, &value) in row.iter().enumerate() {
            match value {
                b'O' => {
                    load += length - counters[col_i];
                    counters[col_i] += 1;
                }
                b'#' => {
                    counters[col_i] = row_i + 1;
                }
                b'.' => {
                    continue;
                }
                _ => unreachable!(),
            }
        }
    }
    load
}

fn roll(grid: &mut Vec<Vec<u8>>) {
    loop {
        let mut changed = false;
        for r in 0..grid.len() - 1 {
            for c in 0..grid[0].len() {
                if grid[r + 1][c] == b'O' && grid[r][c] == b'.' {
                    grid[r][c] = b'O';
                    grid[r + 1][c] = b'.';
                    changed = true;
                }
            }
        }
        if !changed {
            break;
        }
    }
}

fn rotate(grid: &Vec<Vec<u8>>) -> Vec<Vec<u8>> {
    let rows = grid.len();
    let cols = grid[0].len();

    let mut newgrid = vec![vec![0; rows]; cols];

    for r in 0..rows {
        for c in 0..cols {
            newgrid[c][rows - 1 - r] = grid[r][c];
        }
    }

    newgrid
}

fn find_load(grid: &Vec<Vec<u8>>) -> usize {
    let mut load = 0;
    let g_len = grid.len();

    for row in 0..g_len {
        for col in 0..grid[0].len() {
            if grid[row][col] == b'O' {
                load += g_len - row;
            }
        }
    }

    load
}

#[aoc2023::main(14)]
fn main(input: &str) -> (usize, usize) {
    let mut grid: Vec<_> = input.lines().map(|l| l.as_bytes().to_vec()).collect();

    let p1 = p1(&grid);

    let mut cache = HashMap::new();
    for i in 1..1000000000 {
        for _ in 0..4 {
            roll(&mut grid);
            grid = rotate(&grid);
        }
        if let Some(seen_at) = cache.insert(grid.clone(), i) {
            if (1000000000 - i) % (i - seen_at) == 0 {
                break;
            }
        }
    }
    (p1, find_load(&grid))
}
