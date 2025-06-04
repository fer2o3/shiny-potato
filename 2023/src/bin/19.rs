use hashbrown::HashMap;
use itertools::Itertools;

#[derive(Debug, Clone)]
struct Rule {
    category: char,
    is_less_than: bool,
    threshold: usize,
    destination: String,
}

#[derive(Debug)]
struct Workflow {
    rules: Vec<Rule>,
    default_destination: String,
}

type WorkflowMap = HashMap<String, Workflow>;

const CATEGORIES: &str = "xmas";

fn parse_workflows(input: &str) -> WorkflowMap {
    input
        .lines()
        .map(|line| {
            let (name, content) = line.split_once('{').unwrap();
            let content = &content[..content.len() - 1];
            let (rules_str, default) = content.rsplit_once(',').unwrap();

            let rules = rules_str
                .split(',')
                .map(|rule_str| {
                    let (condition, destination) = rule_str.split_once(':').unwrap();
                    let is_less_than = condition.contains('<');
                    let (category, threshold) = condition
                        .split_once(if is_less_than { '<' } else { '>' })
                        .unwrap();

                    Rule {
                        category: category.chars().next().unwrap(),
                        is_less_than,
                        threshold: threshold.parse().unwrap(),
                        destination: destination.to_string(),
                    }
                })
                .collect();

            (
                name.to_string(),
                Workflow {
                    rules,
                    default_destination: default.to_string(),
                },
            )
        })
        .collect()
}

fn parse_parts(input: &str) -> Vec<[usize; 4]> {
    input
        .lines()
        .map(|line| {
            let values: (usize, usize, usize, usize) = line
                .split(|c: char| !c.is_ascii_digit())
                .filter(|s| !s.is_empty())
                .map(|s| s.parse().unwrap())
                .collect_tuple()
                .unwrap();
            [values.0, values.1, values.2, values.3]
        })
        .collect()
}

fn is_part_accepted(workflows: &WorkflowMap, part_values: [usize; 4]) -> bool {
    let mut current = "in";

    while current != "A" && current != "R" {
        let workflow = &workflows[current];

        current = workflow
            .rules
            .iter()
            .find(|rule| {
                let category_index = CATEGORIES.find(rule.category).unwrap();
                let value = part_values[category_index];

                if rule.is_less_than {
                    value < rule.threshold
                } else {
                    value > rule.threshold
                }
            })
            .map(|rule| rule.destination.as_str())
            .unwrap_or(&workflow.default_destination);
    }

    current == "A"
}

fn count_accepted_combinations(
    workflows: &WorkflowMap,
    current: &str,
    mut ranges: [Vec<usize>; 4],
) -> usize {
    match current {
        "A" => return ranges.iter().map(|v| v.len()).product(),
        "R" => return 0,
        _ => {}
    }

    let mut total = 0;
    let workflow = &workflows[current];

    for rule in &workflow.rules {
        let category_index = CATEGORIES.find(rule.category).unwrap();
        let mut new_ranges = ranges.clone();

        let (matching, remaining): (Vec<_>, Vec<_>) =
            ranges[category_index].iter().partition(|&&val| {
                if rule.is_less_than {
                    val < rule.threshold
                } else {
                    val > rule.threshold
                }
            });

        new_ranges[category_index] = matching;
        ranges[category_index] = remaining;

        total += count_accepted_combinations(workflows, &rule.destination, new_ranges);
    }

    total += count_accepted_combinations(workflows, &workflow.default_destination, ranges);
    total
}

#[aoc2023::main(19)]
fn main(input: &str) -> (usize, usize) {
    let (workflow_input, parts_input) = input.split_once("\n\n").unwrap();

    let workflows = parse_workflows(workflow_input);
    let parts = parse_parts(parts_input);

    let part1 = parts
        .iter()
        .filter(|&&part| is_part_accepted(&workflows, part))
        .map(|part| part.iter().sum::<usize>())
        .sum();

    let part2 = count_accepted_combinations(
        &workflows,
        "in",
        std::array::from_fn(|_| (1..=4000).collect()),
    );

    (part1, part2)
}
