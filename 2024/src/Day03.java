import java.util.*;
import java.util.regex.*;

public class Day03 extends Main.Day {

    @Override
    public String[] solve(List<String> input) {
        long part1 = 0, part2 = 0;
        Pattern pattern = Pattern.compile(
            "(mul\\((\\d{1,3}),(\\d{1,3})\\)|do\\(\\)|don't\\(\\))"
        );
        boolean isEnabled = true;

        for (String line : input) {
            Matcher matcher = pattern.matcher(line);
            while (matcher.find()) {
                String instruction = matcher.group();
                if (instruction.startsWith("mul")) {
                    int x = Integer.parseInt(matcher.group(2));
                    int y = Integer.parseInt(matcher.group(3));
                    int prod = x * y;
                    part1 += prod;
                    if (isEnabled) {
                        part2 += prod;
                    }
                } else if (instruction.equals("do()")) {
                    isEnabled = true;
                } else if (instruction.equals("don't()")) {
                    isEnabled = false;
                }
            }
        }

        return new String[] { Long.toString(part1), Long.toString(part2) };
    }
}
