import java.util.*;

public class Day08 extends Main.Day {

    static class Antenna {

        int x, y;
        char freq;

        Antenna(int x, int y, char freq) {
            this.x = x;
            this.y = y;
            this.freq = freq;
        }
    }

    @Override
    public String[] solve(List<String> input) {
        List<Antenna> antennas = new ArrayList<>();
        int maxX = input.get(0).length();
        int maxY = input.size();
        for (int y = 0; y < input.size(); y++) {
            String line = input.get(y);
            for (int x = 0; x < line.length(); x++) {
                char c = line.charAt(x);
                if (c != '.') {
                    antennas.add(new Antenna(x, y, c));
                }
            }
        }

        Set<String> antinodes1 = new HashSet<>();
        Set<String> antinodes2 = new HashSet<>();

        for (int i = 0; i < antennas.size(); i++) {
            for (int j = i + 1; j < antennas.size(); j++) {
                Antenna a1 = antennas.get(i);
                Antenna a2 = antennas.get(j);

                if (a1.freq == a2.freq) {
                    int dx = a2.x - a1.x;
                    int dy = a2.y - a1.y;

                    int x1 = a1.x - dx;
                    int y1 = a1.y - dy;
                    if (isInBounds(x1, y1, maxX, maxY)) {
                        antinodes1.add(x1 + "," + y1);
                    }

                    int x2 = a2.x + dx;
                    int y2 = a2.y + dy;
                    if (isInBounds(x2, y2, maxX, maxY)) {
                        antinodes1.add(x2 + "," + y2);
                    }

                    for (int k = -2 * maxX; k <= 2 * maxX; k++) {
                        int x = a1.x + k * dx;
                        int y = a1.y + k * dy;
                        if (isInBounds(x, y, maxX, maxY)) {
                            antinodes2.add(x + "," + y);
                        }
                    }
                }
            }
        }

        return new String[] {
            Integer.toString(antinodes1.size()),
            Integer.toString(antinodes2.size()),
        };
    }

    private boolean isInBounds(int x, int y, int width, int height) {
        return x >= 0 && x < width && y >= 0 && y < height;
    }
}
