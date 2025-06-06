import java.util.*;
import java.util.stream.*;

public class Day11 extends Main.Day {
    @Override
    public String[] solve(List<String> input) {
        Map<Long, Long> stones = Arrays.stream(input.get(0).split(" "))
                .collect(Collectors.toMap(Long::parseLong, s -> 1L, Long::sum));

        long part1 = 0;
        for (int i = 0; i < 75; i++) {
            stones = stones.entrySet().stream()
                    .flatMap(e -> transform(e.getKey()).stream().map(n -> Map.entry(n, e.getValue())))
                    .collect(Collectors.toMap(Map.Entry::getKey, Map.Entry::getValue, Long::sum));
            if (i == 24)
                part1 = stones.values().stream().mapToLong(Long::longValue).sum();
        }

        return new String[] { String.valueOf(part1),
                String.valueOf(stones.values().stream().mapToLong(Long::longValue).sum()) };
    }

    private List<Long> transform(long num) {
        if (num == 0)
            return List.of(1L);
        String s = String.valueOf(num);
        return s.length() % 2 == 0 ? List.of(Long.parseLong(s.substring(0, s.length() / 2)),
                Long.parseLong(s.substring(s.length() / 2))) : List.of(num * 2024);
    }
}
