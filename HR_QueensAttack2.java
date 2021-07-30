// https://www.hackerrank.com/challenges/queens-attack-2/problem

import java.io.*;
import java.math.*;
import java.security.*;
import java.text.*;
import java.util.*;
import java.util.concurrent.*;
import java.util.function.*;
import java.util.regex.*;
import java.util.stream.*;
import static java.util.stream.Collectors.joining;
import static java.util.stream.Collectors.toList;

class Result {

    /*
     * Complete the 'queensAttack' function below.
     *
     * The function is expected to return an INTEGER.
     * The function accepts following parameters:
     *  1. INTEGER n
     *  2. INTEGER k
     *  3. INTEGER r_q
     *  4. INTEGER c_q
     *  5. 2D_INTEGER_ARRAY obstacles
     */

    public static int queensAttack(int n, int k, int r_q, int c_q, List<List<Integer>> obstacles) {
        // Make obstacles list of each direction, the first obstacle that queen encounterd will be the first of each direction.
        // Get obstacles of downside of the queen, higher row thing will come first (reverse)
        List<List<Integer>> obsDownRow = obstacles.stream()
                                    .filter(o -> o.get(1) == c_q && o.get(0) < r_q)
                                    .sorted(
                                        (p1, p2) -> 
                                        Integer.compare( p1.get(0), p2.get(0) )
                                    )
                                    .collect(Collectors.toList());
        Collections.reverse(obsDownRow);
        
        // Get obstacles of upside of the queen, lower row thing will come first
        List<List<Integer>> obsUpRow = obstacles.stream()
                                    .filter(o -> o.get(1) == c_q && o.get(0) > r_q)
                                    .sorted(
                                        (p1, p2) -> 
                                        Integer.compare( p1.get(0), p2.get(0) )
                                    )
                                    .collect(Collectors.toList());
                                    
        // Get obstacles of rightside of the queen, lower column thing will come first
        List<List<Integer>> obsRightCol = obstacles.stream()
                                    .filter(o -> o.get(0) == r_q && o.get(1) > c_q)
                                    .sorted(
                                        (p1, p2) -> 
                                        Integer.compare( p1.get(1), p2.get(1) )
                                    )
                                    .collect(Collectors.toList());
                                    
        // Get obstacles of leftside of the queen, higher column thing will come first (reverse)
        List<List<Integer>> obsLeftCol = obstacles.stream()
                                    .filter(o -> o.get(0) == r_q && o.get(1) < c_q)
                                    .sorted(
                                        (p1, p2) -> 
                                        Integer.compare( p1.get(1), p2.get(1) )
                                    )
                                    .collect(Collectors.toList());
        Collections.reverse(obsLeftCol);
        
        // Get obstacles of Right-Up Diagonal of the queen, lower row thing will come first
        List<List<Integer>> obsRUCross = obstacles.stream()
                                        .filter(o -> Math.abs(r_q - o.get(0)) == Math.abs(c_q - o.get(1)))
                                        .filter(o -> r_q - o.get(0) < 0 && c_q - o.get(1) < 0)
                                        .sorted(
                                            (p1, p2) -> 
                                            Integer.compare( p1.get(0), p2.get(0) )
                                        )
                                        .collect(Collectors.toList());
        // Get obstacles of Right-Down Diagonal of the queen, higher row thing will come first (reverse)
        List<List<Integer>> obsRDCross = obstacles.stream()
                                        .filter(o -> Math.abs(r_q - o.get(0)) == Math.abs(c_q - o.get(1)))
                                        .filter(o -> r_q - o.get(0) > 0 && c_q - o.get(1) > 0)
                                        .sorted(
                                            (p1, p2) -> 
                                            Integer.compare( p1.get(0), p2.get(0) )
                                        )
                                        .collect(Collectors.toList());
        Collections.reverse(obsRDCross);
        
        // Get obstacles of Left-Up Diagonal of the queen, lower row thing will come first
        List<List<Integer>> obsLUCross = obstacles.stream()
                                        .filter(o -> Math.abs(r_q - o.get(0)) == Math.abs(c_q - o.get(1)))
                                        .filter(o -> r_q - o.get(0) < 0 && c_q - o.get(1) > 0)
                                        .sorted(
                                            (p1, p2) -> 
                                            Integer.compare( p1.get(0), p2.get(0) )
                                        )
                                        .collect(Collectors.toList());
                                        
        // Get obstacles of Right-Up Diagonal of the queen, lower column thing will come first
        List<List<Integer>> obsLDCross = obstacles.stream()
                                        .filter(o -> Math.abs(r_q - o.get(0)) == Math.abs(c_q - o.get(1)))
                                        .filter(o -> r_q - o.get(0) > 0 && c_q - o.get(1) < 0)
                                        .sorted(
                                            (p1, p2) -> 
                                            Integer.compare( p1.get(1), p2.get(1) )
                                        )
                                        .collect(Collectors.toList());
        
        // Direction counters; able to move;
        int canGoRows = 0;
        int canGoCols = 0;
        int canGoRCross = 0;
        int canGoLCross = 0;
        
        
        if(obsDownRow.size() == 0) {    // If no obstacles, simple math;
            canGoRows += (r_q - 1);
        } else {                        // If any, consider only the first thing of that direction.
            canGoRows += (r_q - obsDownRow.get(0).get(0) - 1);
        }
        
        if(obsUpRow.size() == 0) {
            canGoRows += (n - r_q);
        } else {
            canGoRows += (obsUpRow.get(0).get(0) - r_q - 1);
        }
        
        if(obsRightCol.size() == 0) {
            canGoCols += (n - c_q);
        } else {
            canGoCols += (obsRightCol.get(0).get(1) - c_q - 1);
        }
        
        if(obsLeftCol.size() == 0) {
            canGoCols += (c_q - 1);
        } else {
            canGoCols += (c_q - obsLeftCol.get(0).get(1)- 1);
        }
        
        if(obsRUCross.size() == 0) {
            canGoRCross += Math.min(n - r_q, n - c_q);
        } else {
            canGoRCross += obsRUCross.get(0).get(0) - r_q - 1;
        }
        
        if(obsRDCross.size() == 0) {
            canGoRCross += Math.min(r_q - 1, c_q - 1);
        } else {
            canGoRCross += r_q - obsRDCross.get(0).get(0) - 1;
        }
        
        if(obsLUCross.size() == 0) {
            canGoLCross += Math.min(n - r_q, c_q - 1);
        } else {
            canGoLCross += obsLUCross.get(0).get(0) - r_q - 1;
        }
        
        if(obsLDCross.size() == 0) {
            canGoLCross += Math.min(r_q - 1, n - c_q);
        } else {
            canGoLCross += r_q - obsLDCross.get(0).get(0) - 1;
        }
        
        return canGoRows + canGoCols + canGoRCross + canGoLCross;
    }

}

public class Solution {
    public static void main(String[] args) throws IOException {
        BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter bufferedWriter = new BufferedWriter(new FileWriter(System.getenv("OUTPUT_PATH")));

        String[] firstMultipleInput = bufferedReader.readLine().replaceAll("\\s+$", "").split(" ");

        int n = Integer.parseInt(firstMultipleInput[0]);

        int k = Integer.parseInt(firstMultipleInput[1]);

        String[] secondMultipleInput = bufferedReader.readLine().replaceAll("\\s+$", "").split(" ");

        int r_q = Integer.parseInt(secondMultipleInput[0]);

        int c_q = Integer.parseInt(secondMultipleInput[1]);

        List<List<Integer>> obstacles = new ArrayList<>();

        IntStream.range(0, k).forEach(i -> {
            try {
                obstacles.add(
                    Stream.of(bufferedReader.readLine().replaceAll("\\s+$", "").split(" "))
                        .map(Integer::parseInt)
                        .collect(toList())
                );
            } catch (IOException ex) {
                throw new RuntimeException(ex);
            }
        });

        int result = Result.queensAttack(n, k, r_q, c_q, obstacles);

        bufferedWriter.write(String.valueOf(result));
        bufferedWriter.newLine();

        bufferedReader.close();
        bufferedWriter.close();
    }
}
