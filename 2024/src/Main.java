import java.nio.file.Files;
import java.nio.file.Path;
import java.util.List;
import java.time.Instant;

public class Main {

    public static class Day {
       public String[] solve(List<String> input) { 
           return new String[]{"Not implemented", "Not implemented"}; 
       }
    }

    public static void main(String[] args) throws Exception {
        if (args.length < 1) {
            System.out.println("Usage: java Main <day|all> [input_type]");
            return;
        }
        
        String inputType = args.length > 1 ? args[1] : "input";
        
        if (args[0].equals("all")) {
            runAllDays(inputType);
        } else {
            int day = Integer.parseInt(args[0]);
            runDay(day, inputType);
        }
    }
    
    private static void runDay(int day, String inputType) throws Exception {
        String inputFile = inputType.equals("test") 
            ? String.format("test_inputs/%02d.in", day)
            : String.format("inputs/%02d.in", day);
            
        List<String> input = Files.readAllLines(Path.of(inputFile));
        
        var solution = (Day) Class.forName("Day" + String.format("%02d", day))
                                .getDeclaredConstructor()
                                .newInstance();
        
        long start = Instant.now().toEpochMilli();
        String[] results = solution.solve(input);
        long time = Instant.now().toEpochMilli() - start;
       
        System.out.printf("Part 1: %s%nPart 2: %s%nTime: %dms%n\n", 
                         results[0], results[1], time);
    }
    
    private static void runAllDays(String inputType) throws Exception {
        System.out.println("Running all days...");
        for (int day = 1; day <= 25; day++) {
            System.out.printf("Day %02d\n", day);
            runDay(day, inputType);
        }
    }
}
