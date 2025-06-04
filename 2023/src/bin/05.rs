use itertools::Itertools;

fn plant_seeds(seeds: Vec<usize>, mappings: &[Vec<(usize, usize, usize)>]) -> usize {
    mappings
        .iter()
        .fold(seeds, |seeds, mapping| {
            seeds
                .iter()
                .map(|&seed| {
                    mapping
                        .iter()
                        .find(|&&(_, src, step)| (src..src + step).contains(&seed))
                        .map(|(dst, src, _)| dst + seed - src)
                        .unwrap_or(seed)
                })
                .collect()
        })
        .iter()
        .min()
        .copied()
        .unwrap()
}

fn plant_ultra_seeds(seeds: Vec<usize>, mappings: &[Vec<(usize, usize, usize)>]) -> usize {
    let seeds = seeds
        .iter()
        .tuples()
        .map(|(&a, step)| (a, a + step))
        .collect::<Vec<_>>();

    mappings
        .iter()
        .fold(seeds, |seeds, mapping| {
            seeds
                .iter()
                .flat_map(|&(start, step)| {
                    let mut mapped = Vec::new();
                    let mut unmapped = vec![(start, step)];

                    for &(dst, src, step) in mapping {
                        let mut temp = Vec::new();

                        for (start, end) in unmapped {
                            let r1 = (start, end.min(src));
                            let r2 = (start.max(src), (src + step).min(end));
                            let r3 = ((src + step).max(start), end);

                            if r1.1 > r1.0 {
                                temp.push(r1);
                            }

                            if r2.1 > r2.0 {
                                mapped.push((r2.0 - src + dst, r2.1 - src + dst));
                            }

                            if r3.1 > r3.0 {
                                temp.push(r3);
                            }
                        }

                        unmapped = temp;
                    }

                    mapped.extend(unmapped);
                    mapped
                })
                .collect::<Vec<_>>()
        })
        .iter()
        .map(|&(s, _)| s)
        .min()
        .unwrap()
}

#[aoc2023::main(05)]
fn main(input: &str) -> (usize, usize) {
    let (seeds, rest) = input.split_once("\n\n").unwrap();

    let seeds: Vec<usize> = seeds
        .split_whitespace()
        .skip(1)
        .map(|num| num.parse().unwrap())
        .collect();

    let mappings: Vec<Vec<(usize, usize, usize)>> = rest
        .split("\n\n")
        .map(|s| {
            s.split('\n')
                .skip(1)
                .map(|l| {
                    l.split_whitespace()
                        .map(|s| s.parse().unwrap())
                        .collect_tuple()
                        .unwrap()
                })
                .collect()
        })
        .collect();

    let p1 = plant_seeds(seeds.clone(), &mappings);
    let p2 = plant_ultra_seeds(seeds, &mappings);
    (p1, p2)
}
