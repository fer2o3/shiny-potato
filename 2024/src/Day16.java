import java.util.*;
import java.util.stream.*;

public class Day16 extends Main.Day {
    private static final int[][] DIRS = { { 0, 1 }, { 1, 0 }, { 0, -1 }, { -1, 0 } };

    @Override
    public String[] solve(List<String> input) {
        char[][] grid = input.stream().map(String::toCharArray).toArray(char[][]::new);
        int[] start = findPos(grid, 'S'), end = findPos(grid, 'E');

        Map<String, Integer> dist = new HashMap<>();
        Map<String, Set<String>> prev = new HashMap<>();
        PriorityQueue<int[]> pq = new PriorityQueue<>(Comparator.comparingInt(a -> a[3]));

        String startKey = start[0] + "," + start[1] + ",0";
        dist.put(startKey, 0);
        pq.offer(new int[] { start[0], start[1], 0, 0 });

        while (!pq.isEmpty()) {
            int[] curr = pq.poll();
            int r = curr[0], c = curr[1], dir = curr[2], cost = curr[3];
            String key = r + "," + c + "," + dir;

            if (cost > dist.getOrDefault(key, Integer.MAX_VALUE))
                continue;

            for (int newDir = 0; newDir < 4; newDir++) {
                int nr = r + DIRS[newDir][0], nc = c + DIRS[newDir][1];
                if (nr < 0 || nr >= grid.length || nc < 0 || nc >= grid[0].length || grid[nr][nc] == '#')
                    continue;

                int turnCost = 0;
                if (newDir != dir) {
                    int diff = Math.abs(newDir - dir);
                    turnCost = (diff == 2) ? 2000 : 1000;
                }

                int newCost = cost + turnCost + 1;
                addState(dist, prev, pq, nr, nc, newDir, newCost, key);
            }
        }

        int minCost = IntStream.range(0, 4)
                .map(d -> dist.getOrDefault(end[0] + "," + end[1] + "," + d, Integer.MAX_VALUE))
                .min().orElse(Integer.MAX_VALUE);

        Set<String> optimalTiles = new HashSet<>();
        Queue<String> q = new LinkedList<>();

        IntStream.range(0, 4)
                .mapToObj(d -> end[0] + "," + end[1] + "," + d)
                .filter(k -> dist.getOrDefault(k, Integer.MAX_VALUE) == minCost)
                .forEach(q::offer);

        Set<String> visited = new HashSet<>();
        while (!q.isEmpty()) {
            String curr = q.poll();
            if (!visited.add(curr))
                continue;

            String[] parts = curr.split(",");
            optimalTiles.add(parts[0] + "," + parts[1]);

            prev.getOrDefault(curr, Collections.emptySet()).forEach(q::offer);
        }

        return new String[] { String.valueOf(minCost), String.valueOf(optimalTiles.size()) };
    }

    private int[] findPos(char[][] grid, char target) {
        for (int i = 0; i < grid.length; i++)
            for (int j = 0; j < grid[0].length; j++)
                if (grid[i][j] == target)
                    return new int[] { i, j };
        return new int[] { 0, 0 };
    }

    private void addState(Map<String, Integer> dist, Map<String, Set<String>> prev,
            PriorityQueue<int[]> pq, int r, int c, int dir, int cost, String from) {
        String key = r + "," + c + "," + dir;
        int oldCost = dist.getOrDefault(key, Integer.MAX_VALUE);

        if (cost <= oldCost) {
            if (cost < oldCost) {
                dist.put(key, cost);
                prev.put(key, new HashSet<>());
                pq.offer(new int[] { r, c, dir, cost });
            }
            prev.get(key).add(from);
        }
    }
}
