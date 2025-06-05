import java.util.*;

public class Day01 extends Main.Day {

    @Override
    public String[] solve(List<String> input) {

        List<Integer> left = new ArrayList<>();
        List<Integer> right = new ArrayList<>();
        
        for (String line : input) {
            String[] parts = line.trim().split("\\s+");
            left.add(Integer.parseInt(parts[0]));
            right.add(Integer.parseInt(parts[1]));
        }
        
        Collections.sort(left);
        Collections.sort(right);
        
        long distance = 0;
        for (int i = 0; i < left.size(); i++) {
            distance += Math.abs(left.get(i) - right.get(i));
        }
        
        Map<Integer, Integer> frequency = new HashMap<>();
        right.forEach(n -> frequency.merge(n, 1, Integer::sum));

   
        long score = left.stream()
            .mapToLong(n -> (long)n * frequency.getOrDefault(n, 0))
            .sum();   

        return new String[]{Long.toString(distance), Long.toString(score)};    
    }

}
