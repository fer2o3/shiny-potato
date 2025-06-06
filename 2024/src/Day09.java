import java.util.*;
import java.util.stream.*;

public class Day09 extends Main.Day {
    @Override
    public String[] solve(List<String> input) {
        int[] sizes = input.get(0).chars().map(c -> c - '0').toArray();
        int[] disk1 = buildDisk(sizes), disk2 = buildDisk(sizes);
        return new String[]{String.valueOf(compact1(disk1)), String.valueOf(compact2(disk2))};
    }
    
    private int[] buildDisk(int[] sizes) {
        int[] disk = new int[IntStream.of(sizes).sum()];
        Arrays.fill(disk, -1);
        for (int i = 0, pos = 0, id = 0; i < sizes.length; i += 2, id++) {
            Arrays.fill(disk, pos, pos + sizes[i], id);
            pos += sizes[i] + (i + 1 < sizes.length ? sizes[i + 1] : 0);
        }
        return disk;
    }
    
    private long compact1(int[] disk) {
        for (int l = disk.length - 1; l >= 0; l--) {
            if (disk[l] >= 0) {
                for (int f = 0; f < l; f++) {
                    if (disk[f] == -1) {
                        disk[f] = disk[l];
                        disk[l] = -1;
                        break;
                    }
                }
            }
        }
        return checksum(disk);
    }
    
    private long compact2(int[] disk) {
        for (int id = IntStream.of(disk).max().orElse(0); id >= 0; id--) {
            final int fId = id;
            int start = IntStream.range(0, disk.length).filter(i -> disk[i] == fId).findFirst().orElse(-1);
            if (start == -1) continue;
            int size = (int) IntStream.of(disk).filter(x -> x == fId).count();
            
            for (int i = 0; i < start; i++) {
                if (IntStream.range(i, Math.min(i + size, disk.length)).allMatch(j -> disk[j] == -1)) {
                    IntStream.range(0, disk.length).filter(j -> disk[j] == fId).forEach(j -> disk[j] = -1);
                    IntStream.range(i, i + size).forEach(j -> disk[j] = fId);
                    break;
                }
            }
        }
        return checksum(disk);
    }
    
    private long checksum(int[] disk) {
        return IntStream.range(0, disk.length).filter(i -> disk[i] >= 0).mapToLong(i -> (long) i * disk[i]).sum();
    }
}

