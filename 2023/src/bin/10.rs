use itertools::Itertools;
use std::collections::VecDeque;

fn next_pos_from_pipe(pipe: u8, pos: (usize, usize)) -> Vec<(isize, isize)> {
    let (x, y) = (pos.0 as isize, pos.1 as isize);
    match pipe {
        b'|' => vec![(x + 1, y), (x - 1, y)],
        b'-' => vec![(x, y + 1), (x, y - 1)],
        b'L' => vec![(x, y + 1), (x - 1, y)],
        b'J' => vec![(x, y - 1), (x - 1, y)],
        b'7' => vec![(x, y - 1), (x + 1, y)],
        b'F' => vec![(x, y + 1), (x + 1, y)],
        b'.' => vec![],
        _ => unreachable!(),
    }
}

fn bfs(grid: &[Vec<u8>], start: (usize, usize)) -> (usize, usize) {
    let mut visited = vec![vec![false; grid[0].len()]; grid.len()];
    visited[start.0][start.1] = true;
    let mut queue: VecDeque<_> = vec![(start.0, start.1, 0)].into_iter().collect();
    let mut max_len: usize = 0;

    while let Some((x, y, len)) = queue.pop_front() {
        for (x, y) in &next_pos_from_pipe(grid[x][y], (x, y)) {
            let (nx, ny) = (*x as usize, *y as usize);
            let Some(&_square) = grid.get(nx).and_then(|row| row.get(ny)) else {
                continue;
            };
            if !visited[nx][ny] {
                visited[nx][ny] = true;
                queue.push_back((nx, ny, len + 1));
                max_len = len + 1;
            }
        }
    }

    let mut outside: usize = 0;
    for i in 0..grid.len() {
        let mut north = 0;
        for j in 0..grid[0].len() {
            let cur: u8 = grid[i][j];
            if visited[i][j] {
                if matches!(cur, b'|' | b'L' | b'J') {
                    north += 1;
                }
            } else if north % 2 == 1 {
                outside += 1;
            }
        }
    }

    (max_len, outside)
}

#[aoc2023::main(10)]
fn main(input: &str) -> (usize, usize) {
    let mut grid = input
        .lines()
        .map(|l| l.as_bytes().to_vec())
        .collect::<Vec<_>>();

    let (sx, sy) = (0..grid.len())
        .cartesian_product(0..grid[0].len())
        .find(|&(x, y)| grid[x][y] == b'S')
        .unwrap();

    grid[sx][sy] = b'L';

    bfs(&grid, (sx, sy))
}
