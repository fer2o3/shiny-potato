import java.util.*;
import java.util.stream.*;

public class Day14 extends Main.Day {
    @Override
    public String[] solve(List<String> input) {
        int[][] robots = input.stream().map(this::parseRobot).toArray(int[][]::new);
        int w = 101, h = 103;

        long part1 = getSafety(moveRobots(robots, 100, w, h), w, h);
        int part2 = IntStream.iterate(1, i -> i + 1).filter(t -> hasLine(moveRobots(robots, t, w, h), w, h)).findFirst()
                .orElse(0);

        return new String[] { String.valueOf(part1), String.valueOf(part2) };
    }

    private int[] parseRobot(String line) {
        return Arrays.stream(line.replaceAll("[pv=]", "").split("[ ,]"))
                .filter(s -> !s.isEmpty())
                .mapToInt(Integer::parseInt)
                .toArray();
    }

    private int[][] moveRobots(int[][] robots, int time, int w, int h) {
        return Arrays.stream(robots).map(r -> new int[] {
                (r[0] + r[2] * time % w + w) % w,
                (r[1] + r[3] * time % h + h) % h
        }).toArray(int[][]::new);
    }

    private long getSafety(int[][] robots, int w, int h) {
        int[] quads = new int[4];
        for (int[] r : robots) {
            if (r[0] != w / 2 && r[1] != h / 2) {
                quads[(r[0] < w / 2 ? 0 : 1) + (r[1] < h / 2 ? 0 : 2)]++;
            }
        }
        return Arrays.stream(quads).asLongStream().reduce(1, (a, b) -> a * b);
    }

    private boolean hasLine(int[][] robots, int w, int h) {
        Set<String> positions = Arrays.stream(robots).map(r -> r[0] + "," + r[1]).collect(Collectors.toSet());
        return IntStream.range(0, h)
                .anyMatch(y -> IntStream.range(0, w - 9)
                        .anyMatch(x -> IntStream.range(x, x + 10).allMatch(i -> positions.contains(i + "," + y))))
                ||
                IntStream.range(0, w).anyMatch(x -> IntStream.range(0, h - 9)
                        .anyMatch(y -> IntStream.range(y, y + 10).allMatch(i -> positions.contains(x + "," + i))));
    }
}
