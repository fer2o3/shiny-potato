import java.util.*;
import java.util.stream.*;

public class Day25 extends Main.Day {
    @Override
    public String[] solve(List<String> input) {
        List<List<String>> schematics = splitSchematics(input);

        List<int[]> locks = schematics.stream()
                .filter(s -> s.get(0).charAt(0) == '#')
                .map(this::parseLock)
                .collect(Collectors.toList());

        List<int[]> keys = schematics.stream()
                .filter(s -> s.get(0).charAt(0) == '.')
                .map(this::parseKey)
                .collect(Collectors.toList());

        long fits = locks.stream()
                .mapToLong(lock -> keys.stream()
                        .mapToLong(key -> IntStream.range(0, 5)
                                .allMatch(i -> lock[i] + key[i] <= 7) ? 1 : 0)
                        .sum())
                .sum();

        return new String[] { String.valueOf(fits), "Merry Christmas! KACHOW !" };
    }

    private List<List<String>> splitSchematics(List<String> input) {
        List<List<String>> result = new ArrayList<>();
        List<String> current = new ArrayList<>();

        for (String line : input) {
            if (line.isEmpty()) {
                if (!current.isEmpty()) {
                    result.add(new ArrayList<>(current));
                    current.clear();
                }
            } else {
                current.add(line);
            }
        }
        if (!current.isEmpty())
            result.add(current);
        return result;
    }

    private int[] parseLock(List<String> schematic) {
        return IntStream.range(0, 5)
                .map(col -> {
                    for (int row = 0; row < schematic.size(); row++) {
                        if (schematic.get(row).charAt(col) == '.') {
                            return row;
                        }
                    }
                    return schematic.size();
                })
                .toArray();
    }

    private int[] parseKey(List<String> schematic) {
        return IntStream.range(0, 5)
                .map(col -> {
                    int height = 0;
                    for (int row = schematic.size() - 1; row >= 0; row--) {
                        if (schematic.get(row).charAt(col) == '#') {
                            height++;
                        } else {
                            break;
                        }
                    }
                    return height;
                })
                .toArray();
    }
}
