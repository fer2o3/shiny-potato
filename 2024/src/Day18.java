import java.util.*;
import java.util.stream.*;

public class Day18 extends Main.Day {
    private static final int[][] DIRS = { { 0, 1 }, { 1, 0 }, { 0, -1 }, { -1, 0 } };
    private static final int SIZE = 71;

    @Override
    public String[] solve(List<String> input) {
        List<int[]> bytes = input.stream()
                .map(line -> Arrays.stream(line.split(",")).mapToInt(Integer::parseInt).toArray())
                .collect(Collectors.toList());

        Set<String> blocked1024 = bytes.stream().limit(1024)
                .map(p -> p[0] + "," + p[1]).collect(Collectors.toSet());

        int part1 = bfs(blocked1024);

        int left = 0, right = bytes.size() - 1, result = -1;
        while (left <= right) {
            int mid = (left + right) / 2;
            Set<String> blocked = bytes.stream().limit(mid + 1)
                    .map(p -> p[0] + "," + p[1]).collect(Collectors.toSet());

            if (bfs(blocked) == -1) {
                result = mid;
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }

        return new String[] { String.valueOf(part1),
                result >= 0 ? bytes.get(result)[0] + "," + bytes.get(result)[1] : "No solution" };
    }

    private int bfs(Set<String> blocked) {
        Queue<int[]> queue = new LinkedList<>();
        Set<String> visited = new HashSet<>();

        queue.offer(new int[] { 0, 0, 0 });
        visited.add("0,0");

        while (!queue.isEmpty()) {
            int[] curr = queue.poll();
            int x = curr[0], y = curr[1], dist = curr[2];

            if (x == SIZE - 1 && y == SIZE - 1)
                return dist;

            for (int[] dir : DIRS) {
                int nx = x + dir[0], ny = y + dir[1];
                String key = nx + "," + ny;

                if (nx >= 0 && nx < SIZE && ny >= 0 && ny < SIZE &&
                        !blocked.contains(key) && !visited.contains(key)) {
                    queue.offer(new int[] { nx, ny, dist + 1 });
                    visited.add(key);
                }
            }
        }
        return -1;
    }
}
