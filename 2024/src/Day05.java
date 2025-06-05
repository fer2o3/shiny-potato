import java.util.*;

public class Day05 extends Main.Day {

    @Override
    public String[] solve(List<String> input) {
        Map<Integer, Set<Integer>> graph = new HashMap<>();
        List<List<Integer>> updates = new ArrayList<>();
        boolean parsingRules = true;

        for (String line : input) {
            if (line.isEmpty()) {
                parsingRules = false;
                continue;
            }

            if (parsingRules) {
                String[] parts = line.split("\\|");
                int before = Integer.parseInt(parts[0]);
                int after = Integer.parseInt(parts[1]);
                graph.computeIfAbsent(before, k -> new HashSet<>()).add(after);
            } else {
                List<Integer> update = new ArrayList<>();
                for (String num : line.split(",")) {
                    update.add(Integer.parseInt(num));
                }
                updates.add(update);
            }
        }

        long part1 = 0;
        long part2 = 0;

        for (List<Integer> update : updates) {
            if (isValid(update, graph)) {
                part1 += update.get(update.size() / 2);
            } else {
                part2 += fixOrder(new ArrayList<>(update), graph);
            }
        }

        return new String[] { Long.toString(part1), Long.toString(part2) };
    }

    private boolean isValid(
        List<Integer> update,
        Map<Integer, Set<Integer>> rules
    ) {
        for (int i = 0; i < update.size(); i++) {
            for (int j = i + 1; j < update.size(); j++) {
                int first = update.get(i);
                int second = update.get(j);
                if (
                    rules.containsKey(second) &&
                    rules.get(second).contains(first)
                ) {
                    return false;
                }
            }
        }
        return true;
    }

    private int fixOrder(
        List<Integer> order,
        Map<Integer, Set<Integer>> rules
    ) {
        for (int i = 0; i < order.size(); i++) {
            for (int j = i + 1; j < order.size(); j++) {
                if (
                    rules.containsKey(order.get(j)) &&
                    rules.get(order.get(j)).contains(order.get(i))
                ) {
                    int temp = order.get(i);
                    order.set(i, order.get(j));
                    order.set(j, temp);
                }
            }
        }
        return order.get(order.size() / 2);
    }
}
