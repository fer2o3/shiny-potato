import java.util.*;
import java.util.stream.*;

public class Day23 extends Main.Day {
    private Map<String, Set<String>> graph = new HashMap<>();

    @Override
    public String[] solve(List<String> input) {
        input.forEach(line -> {
            String[] parts = line.split("-");
            graph.computeIfAbsent(parts[0], k -> new HashSet<>()).add(parts[1]);
            graph.computeIfAbsent(parts[1], k -> new HashSet<>()).add(parts[0]);
        });

        long part1 = graph.keySet().stream()
                .flatMap(a -> graph.get(a).stream()
                        .filter(b -> a.compareTo(b) < 0)
                        .flatMap(b -> graph.get(a).stream()
                                .filter(c -> b.compareTo(c) < 0 && graph.get(b).contains(c))
                                .filter(c -> a.charAt(0) == 't' || b.charAt(0) == 't' || c.charAt(0) == 't')
                                .map(c -> Set.of(a, b, c))))
                .count();

        Set<String> largest = bronKerbosch(new HashSet<>(), new HashSet<>(graph.keySet()), new HashSet<>())
                .stream().max(Comparator.comparingInt(Set::size)).orElse(Set.of());

        return new String[] { String.valueOf(part1),
                largest.stream().sorted().collect(Collectors.joining(",")) };
    }

    private List<Set<String>> bronKerbosch(Set<String> r, Set<String> p, Set<String> x) {
        if (p.isEmpty() && x.isEmpty())
            return List.of(new HashSet<>(r));

        List<Set<String>> cliques = new ArrayList<>();
        String pivot = Stream.concat(p.stream(), x.stream())
                .max(Comparator.comparingInt(v -> (int) p.stream().filter(graph.get(v)::contains).count()))
                .orElse("");

        Set<String> candidates = new HashSet<>(p);
        candidates.removeAll(graph.getOrDefault(pivot, Set.of()));

        for (String v : new HashSet<>(candidates)) {
            Set<String> neighbors = graph.get(v);
            cliques.addAll(bronKerbosch(
                    Stream.concat(r.stream(), Stream.of(v)).collect(Collectors.toSet()),
                    p.stream().filter(neighbors::contains).collect(Collectors.toSet()),
                    x.stream().filter(neighbors::contains).collect(Collectors.toSet())));
            p.remove(v);
            x.add(v);
        }
        return cliques;
    }
}
