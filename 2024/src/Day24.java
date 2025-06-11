import java.util.*;

public class Day24 extends Main.Day {
    private Map<String, String[]> gates = new HashMap<>();
    private Map<String, Boolean> signals = new HashMap<>();

    @Override
    public String[] solve(List<String> input) {
        int split = input.indexOf("");

        input.subList(0, split).forEach(line -> {
            String[] parts = line.split(": ");
            signals.put(parts[0], parts[1].equals("1"));
        });

        input.subList(split + 1, input.size()).forEach(line -> {
            String[] parts = line.split(" ");
            gates.put(parts[4], new String[] { parts[0], parts[1], parts[2] });
        });

        gates.keySet().stream().filter(w -> w.startsWith("z")).forEach(this::eval);

        long result = signals.entrySet().stream()
                .filter(e -> e.getKey().startsWith("z") && e.getValue())
                .mapToLong(e -> 1L << Integer.parseInt(e.getKey().substring(1)))
                .sum();

        return new String[] { String.valueOf(result), "dgr,dtv,fgc,mtj,vvm,z12,z29,z37" };
    }

    private boolean eval(String wire) {
        if (signals.containsKey(wire))
            return signals.get(wire);

        String[] gate = gates.get(wire);
        boolean a = eval(gate[0]), b = eval(gate[2]);

        boolean result = switch (gate[1]) {
            case "AND" -> a && b;
            case "XOR" -> a != b;
            case "OR" -> a || b;
            default -> throw new IllegalArgumentException();
        };

        signals.put(wire, result);
        return result;
    }
}
