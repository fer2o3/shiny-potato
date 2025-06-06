import java.util.*;

public class Day12 extends Main.Day {
    private static final int[][] DIRS = { { 0, 1 }, { 1, 0 }, { 0, -1 }, { -1, 0 } };

    @Override
    public String[] solve(List<String> input) {
        char[][] grid = input.stream().map(String::toCharArray).toArray(char[][]::new);
        boolean[][] visited = new boolean[grid.length][grid[0].length];
        long part1 = 0, part2 = 0;

        for (int i = 0; i < grid.length; i++) {
            for (int j = 0; j < grid[0].length; j++) {
                if (!visited[i][j]) {
                    Set<String> plots = new HashSet<>();
                    floodFill(grid, i, j, visited, plots);
                    int area = plots.size();
                    int perimeter = plots.stream().mapToInt(p -> countEdges(grid, p)).sum();
                    int sides = countSides(grid, plots, grid[i][j]);
                    part1 += (long) area * perimeter;
                    part2 += (long) area * sides;
                }
            }
        }

        return new String[] { String.valueOf(part1), String.valueOf(part2) };
    }

    private void floodFill(char[][] grid, int r, int c, boolean[][] visited, Set<String> plots) {
        if (r < 0 || r >= grid.length || c < 0 || c >= grid[0].length ||
                visited[r][c] || (plots.size() > 0 && grid[r][c] != getType(grid, plots.iterator().next())))
            return;

        visited[r][c] = true;
        plots.add(r + "," + c);
        for (int[] d : DIRS)
            floodFill(grid, r + d[0], c + d[1], visited, plots);
    }

    private int countEdges(char[][] grid, String plot) {
        int[] pos = Arrays.stream(plot.split(",")).mapToInt(Integer::parseInt).toArray();
        return (int) Arrays.stream(DIRS).filter(d -> !inBounds(grid, pos[0] + d[0], pos[1] + d[1]) ||
                grid[pos[0] + d[0]][pos[1] + d[1]] != grid[pos[0]][pos[1]]).count();
    }

    private int countSides(char[][] grid, Set<String> plots, char type) {
        Set<String> sides = new HashSet<>();
        for (String plot : plots) {
            int[] pos = Arrays.stream(plot.split(",")).mapToInt(Integer::parseInt).toArray();
            for (int[] d : DIRS) {
                if (inBounds(grid, pos[0] + d[0], pos[1] + d[1]) && grid[pos[0] + d[0]][pos[1] + d[1]] == type)
                    continue;
                int r = pos[0], c = pos[1];
                while (plots.contains((r + d[1]) + "," + (c + d[0])) &&
                        (!inBounds(grid, r + d[0], c + d[1]) || grid[r + d[0]][c + d[1]] != type)) {
                    r += d[1];
                    c += d[0];
                }
                sides.add(r + "," + c + "," + d[0] + "," + d[1]);
            }
        }
        return sides.size();
    }

    private boolean inBounds(char[][] grid, int r, int c) {
        return r >= 0 && r < grid.length && c >= 0 && c < grid[0].length;
    }

    private char getType(char[][] grid, String plot) {
        int[] pos = Arrays.stream(plot.split(",")).mapToInt(Integer::parseInt).toArray();
        return grid[pos[0]][pos[1]];
    }
}

