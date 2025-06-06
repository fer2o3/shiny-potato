import java.util.*;

public class Day10 extends Main.Day {
    private static final int[][] DIRS = { { 0, 1 }, { 1, 0 }, { 0, -1 }, { -1, 0 } };

    @Override
    public String[] solve(List<String> input) {
        int[][] grid = input.stream().map(s -> s.chars().map(c -> c - '0').toArray()).toArray(int[][]::new);
        List<int[]> heads = new ArrayList<>();

        for (int i = 0; i < grid.length; i++)
            for (int j = 0; j < grid[0].length; j++)
                if (grid[i][j] == 0)
                    heads.add(new int[] { i, j });

        long part1 = heads.stream().mapToLong(h -> dfs(grid, h[0], h[1], 0, new HashSet<>(), true).size()).sum();
        long part2 = heads.stream().mapToLong(h -> dfs(grid, h[0], h[1], 0, new HashSet<>(), false).size()).sum();

        return new String[] { String.valueOf(part1), String.valueOf(part2) };
    }

    private Set<String> dfs(int[][] grid, int r, int c, int h, Set<String> visited, boolean countUnique) {
        if (r < 0 || r >= grid.length || c < 0 || c >= grid[0].length ||
                grid[r][c] != h || visited.contains(r + "," + c))
            return new HashSet<>();

        if (h == 9) {
            Set<String> result = new HashSet<>();
            result.add(countUnique ? r + "," + c : UUID.randomUUID().toString());
            return result;
        }

        visited.add(r + "," + c);
        Set<String> paths = new HashSet<>();
        for (int[] d : DIRS) {
            Set<String> subPaths = dfs(grid, r + d[0], c + d[1], h + 1, new HashSet<>(visited), countUnique);
            paths.addAll(subPaths);
        }
        return paths;
    }
}
