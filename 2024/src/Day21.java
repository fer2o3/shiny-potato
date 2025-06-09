import java.util.*;
import static java.lang.Integer.parseInt;
import static java.lang.Math.*;

public class Day21 extends Main.Day {
    private static final char[][] NUM = {
            "789".toCharArray(),
            "456".toCharArray(),
            "123".toCharArray(),
            " 0A".toCharArray()
    };
    private static final char[][] DIR = {
            " ^A".toCharArray(),
            "<v>".toCharArray()
    };

    private final Map<String, Long> cache = new HashMap<>();

    @Override
    public String[] solve(List<String> input) {
        return new String[] {
                String.valueOf(input.stream().mapToLong(c -> solve(c, 2) * parseInt(c.substring(0, 3))).sum()),
                String.valueOf(input.stream().mapToLong(c -> solve(c, 25) * parseInt(c.substring(0, 3))).sum())
        };
    }

    private long solve(String code, int robots) {
        return length(code, 0, true, find('A', true), robots);
    }

    private long length(String code, int depth, boolean isNum, int[] from, int maxDepth) {
        String key = code + depth + isNum + from[0] + from[1] + maxDepth;
        if (cache.containsKey(key))
            return cache.get(key);

        long total = 0;
        int[] pos = from.clone();
        for (char c : code.toCharArray()) {
            int[] to = find(c, isNum);
            total += getPaths(pos, to, isNum).stream().mapToLong(
                    seq -> depth == maxDepth ? seq.length() : length(seq, depth + 1, false, find('A', false), maxDepth))
                    .min().orElse(0);
            pos = to;
        }

        cache.put(key, total);
        return total;
    }

    private int[] find(char c, boolean isNum) {
        char[][] grid = isNum ? NUM : DIR;
        for (int i = 0; i < grid.length; i++)
            for (int j = 0; j < grid[i].length; j++)
                if (grid[i][j] == c)
                    return new int[] { i, j };
        return new int[] { 0, 0 };
    }

    private List<String> getPaths(int[] from, int[] to, boolean isNum) {
        List<String> result = new ArrayList<>();
        generatePaths(result, "", from, to, isNum);
        return result;
    }

    private void generatePaths(List<String> result, String current, int[] from, int[] to, boolean isNum) {
        if (Arrays.equals(from, to)) {
            result.add(current + "A");
            return;
        }

        char[][] grid = isNum ? NUM : DIR;
        for (var move : new Object[][] {
                { -1, 0, '^' },
                { 0, 1, '>' },
                { 1, 0, 'v' },
                { 0, -1, '<' }
        }) {
            int nr = from[0] + (int) move[0], nc = from[1] + (int) move[1];
            if (nr >= 0 && nr < grid.length && nc >= 0 && nc < grid[0].length &&
                    grid[nr][nc] != ' ' && dist(new int[] { nr, nc }, to) < dist(from, to)) {
                generatePaths(result, current + move[2], new int[] { nr, nc }, to, isNum);
            }
        }
    }

    private int dist(int[] a, int[] b) {
        return abs(a[0] - b[0]) + abs(a[1] - b[1]);
    }
}
