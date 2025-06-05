import java.util.*;

public class Day02 extends Main.Day {

    @Override
    public String[] solve(List<String> input) {
        long part1Count = 0;
        long part2Count = 0;

        for (String line : input) {
            int[] levels = Arrays.stream(line.split(" "))
                .mapToInt(Integer::parseInt)
                .toArray();

            if (isSafe(levels)) {
                part1Count++;
                part2Count++;
                continue;
            }

            for (int i = 0; i < levels.length; i++) {
                int[] newLevels = new int[levels.length - 1];
                for (int j = 0, k = 0; j < levels.length; j++) {
                    if (j != i) {
                        newLevels[k++] = levels[j];
                    }
                }

                if (isSafe(newLevels)) {
                    part2Count++;
                    break;
                }
            }
        }

        return new String[] {
            Long.toString(part1Count),
            Long.toString(part2Count),
        };
    }

    private boolean isSafe(int[] levels) {
        boolean increasing = true;
        boolean decreasing = true;

        for (int i = 1; i < levels.length; i++) {
            int diff = levels[i] - levels[i - 1];

            if (diff <= 0) increasing = false;
            if (diff >= 0) decreasing = false;

            if (Math.abs(diff) < 1 || Math.abs(diff) > 3) {
                return false;
            }
        }

        return increasing || decreasing;
    }
}
