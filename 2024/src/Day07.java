import java.util.*;

public class Day07 extends Main.Day {

    @Override
    public String[] solve(List<String> input) {
        long part1 = 0;
        long part2 = 0;

        for (String line : input) {
            String[] parts = line.split(": ");
            long target = Long.parseLong(parts[0]);

            String[] numStr = parts[1].split(" ");
            long[] numbers = new long[numStr.length];
            for (int i = 0; i < numStr.length; i++) {
                numbers[i] = Long.parseLong(numStr[i]);
            }

            if (tryOps(numbers, target, 0, numbers[0], false)) {
                part1 += target;
            }

            if (tryOps(numbers, target, 0, numbers[0], true)) {
                part2 += target;
            }
        }

        return new String[] { Long.toString(part1), Long.toString(part2) };
    }

    private boolean tryOps(
        long[] numbers,
        long target,
        int pos,
        long cur,
        boolean p2
    ) {
        if (pos == numbers.length - 1) {
            return cur == target;
        }

        if (tryOps(numbers, target, pos + 1, cur + numbers[pos + 1], p2)) {
            return true;
        }

        if (tryOps(numbers, target, pos + 1, cur * numbers[pos + 1], p2)) {
            return true;
        }

        if (p2) {
            String concat =
                String.valueOf(cur) + String.valueOf(numbers[pos + 1]);
            if (tryOps(numbers, target, pos + 1, Long.parseLong(concat), p2)) {
                return true;
            }
        }

        return false;
    }
}
