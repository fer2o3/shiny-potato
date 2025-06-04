fn reflect_columns(pattern: &[&[u8]], difference: usize) -> Option<usize> {
    (0..pattern[0].len() - 1).find(|&col| {
        // Calculate the total number of incorrect elements for the given column
        let incorrect = (0..=col.min(pattern[0].len() - col - 2))
            .map(|dc| {
                let left_index = col - dc;
                let right_index = col + 1 + dc;

                (0..pattern.len())
                    .filter(|&row| pattern[row][left_index] != pattern[row][right_index])
                    .count()
            })
            .sum::<usize>();

        // Check if the total number of incorrect elements matches the specified difference
        incorrect == difference
    })
}

fn reflect_rows(pattern: &[&[u8]], difference: usize) -> Option<usize> {
    (0..pattern.len() - 1).find(|&row| {
        // Calculate the total number of incorrect elements for the given row
        let incorrect = (0..=row.min(pattern.len() - row - 2))
            .map(|dr| {
                let top_index = row - dr;
                let bottom_index = row + 1 + dr;

                (0..pattern[0].len())
                    .filter(|&col| pattern[top_index][col] != pattern[bottom_index][col])
                    .count()
            })
            .sum::<usize>();

        // Check if the total number of incorrect elements matches the specified difference
        incorrect == difference
    })
}

fn solve(patterns: &[Vec<&[u8]>], difference: usize) -> usize {
    patterns
        .iter()
        .map(|pattern| {
            reflect_rows(pattern, difference)
                .map(|row| (row + 1) * 100)
                .or_else(|| reflect_columns(pattern, difference).map(|col| col + 1))
                .expect("Fucked up somewhere")
        })
        .sum()
}

#[aoc2023::main(13)]
fn main(input: &str) -> (usize, usize) {
    let patterns = input
        .split("\n\n")
        .map(|s| s.lines().map(|l| l.as_bytes()).collect::<Vec<_>>())
        .collect::<Vec<_>>();

    (solve(&patterns, 0), solve(&patterns, 1))
}
