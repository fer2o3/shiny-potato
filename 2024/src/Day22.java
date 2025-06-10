import java.util.*;

public class Day22 extends Main.Day {
    @Override
    public String[] solve(List<String> input) {
        Map<Long, Long> sequences = new HashMap<>();
        long part1 = 0;

        for (String line : input) {
            long secret = Long.parseLong(line);
            int[] prices = new int[2001];
            prices[0] = (int) (secret % 10);

            for (int i = 0; i < 2000; i++) {
                secret = evolve(secret);
                prices[i + 1] = (int) (secret % 10);
            }
            part1 += secret;

            Set<Long> seen = new HashSet<>();
            for (int i = 0; i < 1997; i++) {
                long key = (long) (prices[i + 1] - prices[i] + 9) +
                        (long) (prices[i + 2] - prices[i + 1] + 9) * 19 +
                        (long) (prices[i + 3] - prices[i + 2] + 9) * 361 +
                        (long) (prices[i + 4] - prices[i + 3] + 9) * 6859;

                if (seen.add(key)) {
                    sequences.merge(key, (long) prices[i + 4], Long::sum);
                }
            }
        }

        return new String[] {
                String.valueOf(part1),
                String.valueOf(sequences.values().stream().mapToLong(Long::longValue).max().orElse(0))
        };
    }

    private long evolve(long secret) {
        secret = ((secret << 6) ^ secret) & 0xFFFFFF;
        secret = ((secret >> 5) ^ secret) & 0xFFFFFF;
        return ((secret << 11) ^ secret) & 0xFFFFFF;
    }
}
