import java.util.*;
import java.util.stream.*;

public class Day15 extends Main.Day {
    private static final int[][] DIRS = { { -1, 0 }, { 0, 1 }, { 1, 0 }, { 0, -1 } };
    private static final String DIR_CHARS = "^>v<";

    @Override
    public String[] solve(List<String> input) {
        int split = input.indexOf("");
        List<String> gridLines = input.subList(0, split);
        String moves = String.join("", input.subList(split + 1, input.size()));

        char[][] grid1 = gridLines.stream().map(String::toCharArray).toArray(char[][]::new);
        char[][] grid2 = expandGrid(gridLines);

        int[] pos1 = findPlayer(grid1), pos2 = findPlayer(grid2);

        for (char move : moves.toCharArray()) {
            int dir = DIR_CHARS.indexOf(move);
            if (dir >= 0) {
                if (canMove(grid1, pos1[0], pos1[1], dir)) {
                    movePlayer(grid1, pos1, dir);
                }
                if (canMoveWide(grid2, pos2[0], pos2[1], dir)) {
                    movePlayerWide(grid2, pos2, dir);
                }
            }
        }

        return new String[] { String.valueOf(calculateGPS(grid1, 'O')),
                String.valueOf(calculateGPS(grid2, '[')) };
    }

    private char[][] expandGrid(List<String> lines) {
        return lines.stream().map(line -> line.chars()
                .mapToObj(c -> switch (c) {
                    case '#' -> "##";
                    case 'O' -> "[]";
                    case '.' -> "..";
                    case '@' -> "@.";
                    default -> "..";
                }).collect(Collectors.joining()).toCharArray())
                .toArray(char[][]::new);
    }

    private int[] findPlayer(char[][] grid) {
        for (int i = 0; i < grid.length; i++)
            for (int j = 0; j < grid[0].length; j++)
                if (grid[i][j] == '@')
                    return new int[] { i, j };
        return new int[] { 0, 0 };
    }

    private boolean canMove(char[][] grid, int y, int x, int dir) {
        int ny = y + DIRS[dir][0], nx = x + DIRS[dir][1];
        if (grid[ny][nx] == '#')
            return false;
        if (grid[ny][nx] == 'O')
            return canMove(grid, ny, nx, dir);
        return grid[ny][nx] == '.';
    }

    private void movePlayer(char[][] grid, int[] pos, int dir) {
        int y = pos[0], x = pos[1];
        int ny = y + DIRS[dir][0], nx = x + DIRS[dir][1];
        if (grid[ny][nx] == 'O')
            movePlayer(grid, new int[] { ny, nx }, dir);
        grid[ny][nx] = grid[y][x];
        grid[y][x] = '.';
        pos[0] = ny;
        pos[1] = nx;
    }

    private boolean canMoveWide(char[][] grid, int y, int x, int dir) {
        int ny = y + DIRS[dir][0], nx = x + DIRS[dir][1];
        if (grid[ny][nx] == '#')
            return false;
        if (grid[ny][nx] == '.')
            return true;

        boolean vertical = dir == 0 || dir == 2;
        if (grid[ny][nx] == '[') {
            return canMoveWide(grid, ny, nx, dir) &&
                    (!vertical || canMoveWide(grid, ny, nx + 1, dir));
        }
        if (grid[ny][nx] == ']') {
            return canMoveWide(grid, ny, nx, dir) &&
                    (!vertical || canMoveWide(grid, ny, nx - 1, dir));
        }
        return false;
    }

    private void movePlayerWide(char[][] grid, int[] pos, int dir) {
        int y = pos[0], x = pos[1];
        int ny = y + DIRS[dir][0], nx = x + DIRS[dir][1];
        boolean vertical = dir == 0 || dir == 2;

        if (grid[ny][nx] == '[') {
            movePlayerWide(grid, new int[] { ny, nx }, dir);
            if (vertical)
                movePlayerWide(grid, new int[] { ny, nx + 1 }, dir);
        } else if (grid[ny][nx] == ']') {
            movePlayerWide(grid, new int[] { ny, nx }, dir);
            if (vertical)
                movePlayerWide(grid, new int[] { ny, nx - 1 }, dir);
        }

        grid[ny][nx] = grid[y][x];
        grid[y][x] = '.';
        pos[0] = ny;
        pos[1] = nx;
    }

    private long calculateGPS(char[][] grid, char target) {
        return IntStream.range(0, grid.length)
                .flatMap(y -> IntStream.range(0, grid[0].length)
                        .filter(x -> grid[y][x] == target)
                        .map(x -> y * 100 + x))
                .sum();
    }
}
