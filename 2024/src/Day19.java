import java.util.*;
import java.util.stream.*;

public class Day19 extends Main.Day {
    @Override
    public String[] solve(List<String> input) {
        int split = input.indexOf("");
        Set<String> patterns = Arrays.stream(input.get(0).split(","))
                .map(String::trim).collect(Collectors.toSet());
        List<String> designs = input.subList(split + 1, input.size());

        long[] counts = designs.stream().mapToLong(design -> countWays(design, patterns)).toArray();

        return new String[] {
                String.valueOf(Arrays.stream(counts).filter(c -> c > 0).count()),
                String.valueOf(Arrays.stream(counts).sum())
        };
    }

    private long countWays(String design, Set<String> patterns) {
        long[] dp = new long[design.length() + 1];
        dp[design.length()] = 1;

        for (int i = design.length() - 1; i >= 0; i--) {
            for (String pattern : patterns) {
                if (design.startsWith(pattern, i)) {
                    dp[i] += dp[i + pattern.length()];
                }
            }
        }

        return dp[0];
    }
}
