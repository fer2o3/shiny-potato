fn dfs(
    grid: &[&[u8]],
    seen: &mut [Vec<bool>],
    (r, c): (usize, usize),
    dist: usize,
    max_dist: &mut usize,
    part2: bool,
) {
    if r == grid.len() - 1 {
        *max_dist = (*max_dist).max(dist);
        return;
    }
    let dirs = match (grid[r][c], part2) {
        (_, true) | (b'.', _) => &[(-1, 0), (1, 0), (0, -1), (0, 1)][..],
        (b'^', _) => &[(-1, 0)][..],
        (b'>', _) => &[(0, 1)][..],
        (b'v', _) => &[(1, 0)][..],
        (b'<', _) => &[(0, -1)][..],
        _ => return,
    };
    for &(dr, dc) in dirs {
        let (rr, cc) = ((r as isize + dr) as usize, (c as isize + dc) as usize);
        if let Some(&tile) = grid.get(rr).and_then(|row| row.get(cc)) {
            if tile != b'#' && !seen[rr][cc] {
                seen[rr][cc] = true;
                dfs(grid, seen, (rr, cc), dist + 1, max_dist, part2);
                seen[rr][cc] = false;
            }
        }
    }
}

#[aoc2023::main(23)]
fn main(input: &str) -> (usize, usize) {
    let grid: Vec<&[u8]> = input.lines().map(str::as_bytes).collect();
    let mut seen = vec![vec![false; grid[0].len()]; grid.len()];
    let (mut p1, mut p2) = (0, 0);
    dfs(&grid, &mut seen, (0, 1), 0, &mut p1, false);
    dfs(&grid, &mut seen, (0, 1), 0, &mut p2, true);
    (p1, p2)
}
