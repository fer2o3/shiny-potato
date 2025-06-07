import java.util.*;

public class Day13 extends Main.Day {
    @Override
    public String[] solve(List<String> input) {
        long part1 = 0, part2 = 0;
        for (int i = 0; i < input.size(); i += 4) {
            long[] nums = parseNums(input.subList(i, i + 3));
            part1 += solveMachine(nums[0], nums[1], nums[2], nums[3], nums[4], nums[5]);
            part2 += solveMachine(nums[0], nums[1], nums[2], nums[3], nums[4] + 10000000000000L,
                    nums[5] + 10000000000000L);
        }
        return new String[] { String.valueOf(part1), String.valueOf(part2) };
    }

    private long[] parseNums(List<String> lines) {
        return lines.stream()
                .flatMap(line -> Arrays.stream(line.replaceAll("[^0-9,]", "").split(",")))
                .filter(s -> !s.isEmpty())
                .mapToLong(Long::parseLong)
                .toArray();
    }

    private long solveMachine(long ax, long ay, long bx, long by, long px, long py) {
        long det = by * ax - bx * ay;
        if (det == 0)
            return 0;

        long num_a = by * px - bx * py;
        long num_b = ax * py - ay * px;

        if (num_a % det != 0 || num_b % det != 0)
            return 0;

        long a = num_a / det;
        long b = num_b / det;

        return (a >= 0 && b >= 0) ? 3 * a + b : 0;
    }
}
