use hashbrown::{HashMap, HashSet};

fn component_size(graph: &HashMap<&str, HashSet<&str>>, start: &str) -> usize {
    let (mut seen, mut stack) = (HashSet::new(), vec![start]);
    while let Some(node) = stack.pop() {
        if seen.insert(node) {
            stack.extend(&graph[node]);
        }
    }
    seen.len()
}

#[aoc2023::main(25)]
fn main(input: &str) -> (usize, char) {
    let mut graph = HashMap::<_, HashSet<_>>::new();
    for l in input.lines() {
        let (a, rest) = l.split_once(": ").unwrap();
        for b in rest.split(' ') {
            graph.entry(a).or_default().insert(b);
            graph.entry(b).or_default().insert(a);
        }
    }

    for (a, b) in [("krf", "crg"), ("zhg", "fmr"), ("rgv", "jct")] {
        graph.get_mut(a).unwrap().remove(b);
        graph.get_mut(b).unwrap().remove(a);
    }

    let size = component_size(&graph, "jct");
    ((graph.len() - size) * size, '🎄')
}
