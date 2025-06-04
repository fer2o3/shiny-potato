use hashbrown::HashMap;
use std::collections::BinaryHeap;

fn bfs(grid: &Vec<Vec<usize>>, min_move: usize, max_move: usize) -> i64 {
    let mut cache = HashMap::new();
    let mut queue = BinaryHeap::from_iter([(0, (0, 0, (0, 0)))]);

    while let Some((heat, (r, c, d))) = queue.pop() {
        let current_point = (r, c);

        if current_point == (grid.len() - 1, grid[0].len() - 1) {
            return -heat;
        }

        if let Some(&c) = cache.get(&(r, c, d)) {
            if -heat > c {
                continue;
            }
        }

        for (dr, dc) in [(1, 0), (-1, 0), (0, 1), (0, -1)] {
            let new_direction = (dr, dc);

            if new_direction == d || (-dr, -dc) == d {
                continue;
            }

            let mut total_heat = 0;

            for dist in 1..=max_move {
                let n_r = r as isize + dr * dist as isize;
                let n_c = c as isize + dc * dist as isize;

                if n_r < 0 || n_r >= grid.len() as isize || n_c < 0 || n_c >= grid[0].len() as isize
                {
                    continue;
                }

                let n_r = n_r as usize;
                let n_c = n_c as usize;

                total_heat += grid[n_r][n_c] as i64;

                if dist < min_move {
                    continue;
                }

                let n_heat = -heat + total_heat;
                let key = (n_r, n_c, new_direction);

                if n_heat < *cache.get(&key).unwrap_or(&999999999) {
                    cache.insert(key, n_heat);
                    queue.push((-n_heat, key));
                }
            }
        }
    }
    unreachable!();
}

#[aoc2023::main(17)]
fn main(input: &str) -> (usize, usize) {
    let grid: Vec<_> = input
        .lines()
        .map(|l| {
            l.chars()
                .map(|c| c.to_digit(10).unwrap() as usize)
                .collect::<Vec<_>>()
        })
        .collect();

    (bfs(&grid, 1, 3) as usize, bfs(&grid, 4, 10) as usize)
}
