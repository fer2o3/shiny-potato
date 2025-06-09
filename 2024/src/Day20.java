import java.util.*;
import java.util.stream.*;

public class Day20 extends Main.Day {
    private static final int[][] DIRS = { { 0, 1 }, { 1, 0 }, { 0, -1 }, { -1, 0 } };

    @Override
    public String[] solve(List<String> input) {
        char[][] grid = input.stream().map(String::toCharArray).toArray(char[][]::new);
        Map<String, Integer> path = buildPath(grid);

        return new String[] {
                String.valueOf(countCheats(path, 2, 100)),
                String.valueOf(countCheats(path, 20, 100))
        };
    }

    private Map<String, Integer> buildPath(char[][] grid) {
        int[] start = findPos(grid, 'S'), end = findPos(grid, 'E');
        grid[start[0]][start[1]] = grid[end[0]][end[1]] = '.';

        Map<String, Integer> dist = new HashMap<>();
        Queue<int[]> q = new ArrayDeque<>();
        q.offer(new int[] { start[0], start[1], 0 });

        while (!q.isEmpty()) {
            int[] curr = q.poll();
            int r = curr[0], c = curr[1], d = curr[2];
            String key = r + "," + c;

            if (dist.containsKey(key))
                continue;
            dist.put(key, d);

            for (int[] dir : DIRS) {
                int nr = r + dir[0], nc = c + dir[1];
                if (nr >= 0 && nr < grid.length && nc >= 0 && nc < grid[0].length &&
                        grid[nr][nc] == '.' && !dist.containsKey(nr + "," + nc)) {
                    q.offer(new int[] { nr, nc, d + 1 });
                }
            }
        }
        return dist;
    }

    private int countCheats(Map<String, Integer> path, int maxCheat, int minSave) {
        List<int[]> points = path.entrySet().stream()
                .map(e -> {
                    String[] parts = e.getKey().split(",");
                    return new int[] { Integer.parseInt(parts[0]), Integer.parseInt(parts[1]), e.getValue() };
                })
                .sorted(Comparator.comparingInt(a -> a[2]))
                .collect(Collectors.toList());

        return (int) IntStream.range(0, points.size())
                .flatMap(i -> IntStream.range(i + 1, points.size())
                        .filter(j -> {
                            int[] p1 = points.get(i), p2 = points.get(j);
                            int dist = Math.abs(p1[0] - p2[0]) + Math.abs(p1[1] - p2[1]);
                            return dist <= maxCheat && (p2[2] - p1[2] - dist) >= minSave;
                        }))
                .count();
    }

    private int[] findPos(char[][] grid, char target) {
        for (int i = 0; i < grid.length; i++)
            for (int j = 0; j < grid[0].length; j++)
                if (grid[i][j] == target)
                    return new int[] { i, j };
        return new int[] { 0, 0 };
    }
}
