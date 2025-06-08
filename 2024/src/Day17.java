import java.util.*;
import java.util.regex.*;
import java.util.stream.*;

public class Day17 extends Main.Day {
    private static final Pattern NUM = Pattern.compile("\\d+");
    private int[] program;

    @Override
    public String[] solve(List<String> input) {
        var nums = input.stream().flatMap(s -> new Scanner(s).findAll(NUM).map(r -> Long.parseLong(r.group())))
                .toArray(Long[]::new);
        long a = nums[0], b = nums[1], c = nums[2];
        program = Arrays.stream(nums, 3, nums.length).mapToInt(Long::intValue).toArray();

        return new String[] { run(a, b, c), String.valueOf(replicate()) };
    }

    private String run(long a, long b, long c) {
        var out = new ArrayList<Long>();
        for (int ip = 0; ip < program.length; ip += 2) {
            var combo = switch (program[ip + 1]) {
                case 0, 1, 2, 3 -> program[ip + 1];
                case 4 -> a;
                case 5 -> b;
                case 6 -> c;
                default -> 0L;
            };
            switch (program[ip]) {
                case 0 -> a >>= combo;
                case 1 -> b ^= program[ip + 1];
                case 2 -> b = combo & 7;
                case 3 -> {
                    if (a > 0)
                        ip = program[ip + 1] - 2;
                }
                case 4 -> b ^= c;
                case 5 -> out.add(combo & 7);
                case 6 -> b = a >> combo;
                case 7 -> c = a >> combo;
            }
        }
        return out.stream().map(String::valueOf).collect(Collectors.joining(","));
    }

    private long replicate() {
        return findTarget(Arrays.stream(program).boxed().toList(), 0);
    }

    private long findTarget(List<Integer> target, long a) {
        if (target.isEmpty())
            return a;
        for (int d = 0; d < 8; d++) {
            var candidate = (a << 3) | d;
            long b = 0, c = 0, out = 0;
            for (int ip = 0; ip < program.length - 2; ip += 2) {
                var combo = switch (program[ip + 1]) {
                    case 0, 1, 2, 3 -> program[ip + 1];
                    case 4 -> candidate;
                    case 5 -> b;
                    case 6 -> c;
                    default -> 0L;
                };
                switch (program[ip]) {
                    case 1 -> b ^= program[ip + 1];
                    case 2 -> b = combo & 7;
                    case 4 -> b ^= c;
                    case 5 -> out = combo & 7;
                    case 6 -> b = candidate >> combo;
                    case 7 -> c = candidate >> combo;
                }
            }
            if (out == target.getLast()) {
                var newTarget = new ArrayList<>(target);
                newTarget.removeLast();
                var result = findTarget(newTarget, candidate);
                if (result != -1)
                    return result;
            }
        }
        return -1;
    }
}
