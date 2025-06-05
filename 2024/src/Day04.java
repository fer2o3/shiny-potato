import java.util.*;

public class Day04 extends Main.Day {

    private boolean checkMAS(
        char[][] grid,
        int row,
        int col,
        int dRow,
        int dCol
    ) {
        return (
            grid[row][col] == 'M' &&
            grid[row + dRow][col + dCol] == 'A' &&
            grid[row + 2 * dRow][col + 2 * dCol] == 'S'
        );
    }

    private int countXMAS(char[][] grid, int row, int col) {
        int count = 0;
        if (
            checkMAS(grid, row, col, 1, 1) &&
            checkMAS(grid, row, col + 2, 1, -1)
        ) count++;
        if (
            checkMAS(grid, row, col, 1, 1) &&
            checkMAS(grid, row + 2, col, -1, 1)
        ) count++;
        if (
            checkMAS(grid, row + 2, col, -1, 1) &&
            checkMAS(grid, row + 2, col + 2, -1, -1)
        ) count++;
        if (
            checkMAS(grid, row, col + 2, 1, -1) &&
            checkMAS(grid, row + 2, col + 2, -1, -1)
        ) count++;

        return count;
    }

    @Override
    public String[] solve(List<String> input) {
        char[][] grid = new char[input.size()][input.get(0).length()];
        for (int i = 0; i < input.size(); i++) {
            grid[i] = input.get(i).toCharArray();
        }

        // Garbage
        int part1 = 0;
        int[][] directions = {
            { 0, 1 },
            { 1, 0 },
            { 1, 1 },
            { 1, -1 },
            { 0, -1 },
            { -1, 0 },
            { -1, 1 },
            { -1, -1 },
        };
        for (int i = 0; i < grid.length; i++) {
            for (int j = 0; j < grid[0].length; j++) {
                if (grid[i][j] == 'X') {
                    for (int[] dir : directions) {
                        if (
                            i + 3 * dir[0] >= 0 &&
                            i + 3 * dir[0] < grid.length &&
                            j + 3 * dir[1] >= 0 &&
                            j + 3 * dir[1] < grid[0].length
                        ) {
                            if (
                                grid[i + dir[0]][j + dir[1]] == 'M' &&
                                grid[i + 2 * dir[0]][j + 2 * dir[1]] == 'A' &&
                                grid[i + 3 * dir[0]][j + 3 * dir[1]] == 'S'
                            ) {
                                part1++;
                            }
                        }
                    }
                }
            }
        }

        int part2 = 0;
        for (int i = 0; i < grid.length - 2; i++) {
            for (int j = 0; j < grid[0].length - 2; j++) {
                part2 += countXMAS(grid, i, j);
            }
        }

        return new String[] {
            Integer.toString(part1),
            Integer.toString(part2),
        };
    }
}
