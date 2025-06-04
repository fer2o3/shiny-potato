use itertools::enumerate;

#[aoc2023::main(11)]
fn main(input: &str) -> (usize, usize) {
    let grid: Vec<Vec<char>> = input.lines().map(|l| l.chars().collect()).collect();

    let planets: Vec<_> = grid
        .iter()
        .enumerate()
        .flat_map(|(row_i, row)| {
            enumerate(row.iter())
                .filter(|&(_, &value)| value == '#')
                .map(move |(col_i, _)| (row_i, col_i))
        })
        .collect();

    let void_rows: Vec<_> = grid
        .iter()
        .enumerate()
        .filter(|(_, row)| row.iter().all(|&value| value == '.'))
        .map(|(row_i, _)| row_i)
        .collect();

    let void_cols: Vec<_> = (0..grid[0].len())
        .filter(|&col_i| grid.iter().all(|row| row[col_i] == '.'))
        .collect();

    let mut p1: isize = 0;
    let mut p2: isize = 0;

    planets.iter().enumerate().for_each(|(i, &(x, y))| {
        planets.iter().skip(i + 1).for_each(|&(dx, dy)| {
            let mut man_dist1 = (x as isize - dx as isize).abs() + (y as isize - dy as isize).abs();
            let mut man_dist2 = man_dist1;

            for k in x.min(dx)..x.max(dx) {
                if void_rows.contains(&(k as usize)) {
                    man_dist1 += 1;
                    man_dist2 += 999999;
                }
            }

            for l in y.min(dy)..y.max(dy) {
                if void_cols.contains(&(l as usize)) {
                    man_dist1 += 1;
                    man_dist2 += 999999;
                }
            }

            p1 += man_dist1;
            p2 += man_dist2;
        });
    });

    (p1 as usize, p2 as usize)
}
