use hashbrown::HashSet;
use itertools::Itertools;

const DIRECTIONS: [(isize, isize); 4] = [(-1, 0), (1, 0), (0, -1), (0, 1)];

fn bfs(grid: &[&[u8]], start: (isize, isize), steps: usize) -> usize {
    let mut positions = HashSet::from([start]);
    let height = grid.len() as isize;
    let width = grid[0].len() as isize;

    for _ in 0..steps {
        let mut new_positions = HashSet::new();

        for &(r, c) in &positions {
            for (dr, dc) in DIRECTIONS {
                let (nr, nc) = (r + dr, c + dc);

                let grid_r = nr.rem_euclid(height) as usize;
                let grid_c = nc.rem_euclid(width) as usize;

                if grid[grid_r][grid_c] != b'#' {
                    new_positions.insert((nr, nc));
                }
            }
        }
        positions = new_positions;
    }
    positions.len()
}

fn find_polynomial(grid: &[&[u8]], start: (isize, isize), target_steps: usize) -> usize {
    let cycle_len = grid.len();
    let remainder = target_steps % cycle_len;

    let y0 = bfs(grid, start, remainder);
    let y1 = bfs(grid, start, remainder + cycle_len);
    let y2 = bfs(grid, start, remainder + 2 * cycle_len);

    let n = target_steps / cycle_len;

    let a = y0;
    let b = y1 - y0;
    let c = (y2 - 2 * y1 + y0) / 2;

    a + b * n + c * n * (n - 1)
}

fn find_start(grid: &[&[u8]]) -> (isize, isize) {
    (0..grid.len())
        .cartesian_product(0..grid[0].len())
        .find(|&(r, c)| grid[r][c] == b'S')
        .map(|(r, c)| (r as isize, c as isize))
        .expect("Start position 'S' not found")
}

#[aoc2023::main(21)]
fn main(input: &str) -> (usize, usize) {
    let grid: Vec<&[u8]> = input.lines().map(str::as_bytes).collect();
    let start = find_start(&grid);

    let part1 = bfs(&grid, start, 64);
    let part2 = find_polynomial(&grid, start, 26501365);

    (part1, part2)
}
