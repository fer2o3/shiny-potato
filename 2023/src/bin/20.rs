use std::collections::{HashMap, HashSet, VecDeque};

#[derive(Debug, Clone)]
enum ModuleType {
    Broadcaster,
    FlipFlop,
    Conjunction,
}

#[derive(Debug, Clone)]
struct Module {
    module_type: ModuleType,
    destinations: Vec<String>,
}

#[derive(Debug, Clone)]
struct State {
    flip_flop_states: HashSet<String>,
    conjunction_memory: HashMap<String, HashMap<String, bool>>,
}

fn gcd(mut a: usize, mut b: usize) -> usize {
    while b != 0 {
        let temp = b;
        b = a % b;
        a = temp;
    }
    a
}

fn lcm(a: usize, b: usize) -> usize {
    a * b / gcd(a, b)
}

fn lcm_of_slice(values: &[usize]) -> usize {
    values.iter().copied().reduce(lcm).unwrap_or(1)
}

fn parse_modules(input: &str) -> HashMap<String, Module> {
    input
        .lines()
        .map(|line| {
            let (left, right) = line.split_once(" -> ").unwrap();
            let destinations: Vec<String> = right.split(", ").map(String::from).collect();

            let (name, module_type) = if left == "broadcaster" {
                (left.to_string(), ModuleType::Broadcaster)
            } else {
                let name = left[1..].to_string();
                let module_type = match left.chars().next().unwrap() {
                    '%' => ModuleType::FlipFlop,
                    '&' => ModuleType::Conjunction,
                    _ => panic!("Unknown module type"),
                };
                (name, module_type)
            };

            (
                name,
                Module {
                    module_type,
                    destinations,
                },
            )
        })
        .collect()
}

fn initialize_conjunction_memory(
    modules: &HashMap<String, Module>,
) -> HashMap<String, HashMap<String, bool>> {
    let mut conjunction_memory = HashMap::new();

    for (source_name, module) in modules {
        for dest_name in &module.destinations {
            if let Some(dest_module) = modules.get(dest_name) {
                if matches!(dest_module.module_type, ModuleType::Conjunction) {
                    conjunction_memory
                        .entry(dest_name.clone())
                        .or_insert_with(HashMap::new)
                        .insert(source_name.clone(), false);
                }
            }
        }
    }

    conjunction_memory
}

fn simulate_button_press(
    modules: &HashMap<String, Module>,
    state: &mut State,
    target_cycles: &mut [Option<usize>; 4],
    button_press: usize,
) -> (usize, usize) {
    let mut queue = VecDeque::new();
    queue.push_back(("broadcaster".to_string(), "button".to_string(), false));

    let mut low_pulses = 0;
    let mut high_pulses = 0;

    while let Some((current_name, source_name, is_high_pulse)) = queue.pop_front() {
        if is_high_pulse {
            high_pulses += 1;
        } else {
            low_pulses += 1;
        }

        if is_high_pulse && current_name == "mf" {
            let cycle_index = match source_name.as_str() {
                "bh" => 0,
                "jf" => 1,
                "sh" => 2,
                "mz" => 3,
                _ => continue,
            };

            if target_cycles[cycle_index].is_none() {
                target_cycles[cycle_index] = Some(button_press);
            }
        }

        let Some(module) = modules.get(&current_name) else {
            continue;
        };

        let output_pulse = match &module.module_type {
            ModuleType::Broadcaster => Some(false),

            ModuleType::FlipFlop => {
                if is_high_pulse {
                    None
                } else {
                    let was_on = state.flip_flop_states.contains(&current_name);
                    if was_on {
                        state.flip_flop_states.remove(&current_name);
                        Some(false)
                    } else {
                        state.flip_flop_states.insert(current_name.clone());
                        Some(true)
                    }
                }
            }

            ModuleType::Conjunction => {
                state
                    .conjunction_memory
                    .get_mut(&current_name)
                    .unwrap()
                    .insert(source_name, is_high_pulse);

                let all_high = state.conjunction_memory[&current_name]
                    .values()
                    .all(|&pulse| pulse);
                Some(!all_high)
            }
        };

        if let Some(pulse) = output_pulse {
            for dest in &module.destinations {
                queue.push_back((dest.clone(), current_name.clone(), pulse));
            }
        }
    }

    (low_pulses, high_pulses)
}

#[aoc2023::main(20)]
fn main(input: &str) -> (usize, usize) {
    let modules = parse_modules(input);
    let conjunction_memory = initialize_conjunction_memory(&modules);

    let mut state = State {
        flip_flop_states: HashSet::new(),
        conjunction_memory,
    };

    let mut total_low = 0;
    let mut total_high = 0;
    let mut part1 = 0;
    let mut target_cycles = [None; 4];

    for button_press in 1.. {
        let (low, high) =
            simulate_button_press(&modules, &mut state, &mut target_cycles, button_press);
        total_low += low;
        total_high += high;

        if button_press == 1000 {
            part1 = total_low * total_high;
        }

        if target_cycles.iter().all(|cycle| cycle.is_some()) {
            break;
        }
    }

    let part2 = lcm_of_slice(&target_cycles.map(|cycle| cycle.unwrap()));
    (part1, part2)
}
