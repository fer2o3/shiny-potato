import java.util.*;

public class Day06 extends Main.Day {

    private static final int[][] DIRS = {
        { -1, 0 },
        { 0, 1 },
        { 1, 0 },
        { 0, -1 },
    };

    @Override
    public String[] solve(List<String> input) {
        char[][] grid = new char[input.size()][input.get(0).length()];
        int startRow = 0, startCol = 0, startDir = 0;

        for (int i = 0; i < input.size(); i++) {
            String line = input.get(i);
            for (int j = 0; j < line.length(); j++) {
                grid[i][j] = line.charAt(j);
                if (grid[i][j] == '^') {
                    startRow = i;
                    startCol = j;
                    startDir = 0;
                    grid[i][j] = '.';
                }
            }
        }

        int part1 = simulateGuard(grid, startRow, startCol, startDir);

        int part2 = 0;
        for (int i = 0; i < grid.length; i++) {
            for (int j = 0; j < grid[0].length; j++) {
                if (grid[i][j] == '.' && (i != startRow || j != startCol)) {
                    grid[i][j] = '#';
                    if (
                        simulateGuard(grid, startRow, startCol, startDir) == -1
                    ) {
                        part2++;
                    }
                    grid[i][j] = '.';
                }
            }
        }

        return new String[] {
            Integer.toString(part1),
            Integer.toString(part2),
        };
    }

    private int simulateGuard(
        char[][] grid,
        int startRow,
        int startCol,
        int startDir
    ) {
        Set<String> visited = new HashSet<>();
        Set<String> positions = new HashSet<>();
        int row = startRow, col = startCol, dir = startDir;

        while (isInBounds(row, col, grid)) {
            String state = row + "," + col + "," + dir;
            if (!visited.add(state)) {
                return -1;
            }
            positions.add(row + "," + col);

            int nextRow = row + DIRS[dir][0];
            int nextCol = col + DIRS[dir][1];

            if (
                isInBounds(nextRow, nextCol, grid) &&
                grid[nextRow][nextCol] == '#'
            ) {
                dir = (dir + 1) % 4;
            } else {
                row = nextRow;
                col = nextCol;
            }
        }
        return positions.size();
    }

    private boolean isInBounds(int row, int col, char[][] grid) {
        return (
            row >= 0 && row < grid.length && col >= 0 && col < grid[0].length
        );
    }
}
