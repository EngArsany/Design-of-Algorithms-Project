package javaapplication2;

import java.util.*;

/*
 * Tower of Hanoi with 4 Pegs - Frame-Stewart Algorithm
 * Uses Dynamic Programming to find optimal move counts,
 * then generates the actual move sequence recursively.
 */
public class TowerOfHanoi4Peg {

    // DP table: dp4[n] = minimum moves for n disks on 4 pegs
    private static int[] dp4;
    // Optimal split k for each n: split[n] = k that minimises dp4[n]
    private static int[] split;
    // Move counter for tracking actual moves generated
    private static int moveCount;

    // Computes minimum moves for n disks on 3 pegs (classical result). T(n,3) = 2^n - 1
    public static int threeP(int n) {
        return (1 << n) - 1;  // 2^n - 1
    }

    // Builds the DP table for 4-peg Tower of Hanoi using
    public static void buildDPTable(int maxDisks) {
        dp4   = new int[maxDisks + 1];
        split = new int[maxDisks + 1];
        dp4[0] = 0;
        split[0] = 0;

        if (maxDisks >= 1) {
            dp4[1] = 1;
            split[1] = 1;
        }

        for (int n = 2; n <= maxDisks; n++) {
            dp4[n] = Integer.MAX_VALUE;
            split[n] = 1;
            for (int k = 1; k < n; k++) {
                int candidate = 2 * dp4[k] + threeP(n - k);
                if (candidate < dp4[n]) {
                    dp4[n] = candidate;
                    split[n] = k;
                }
            }
        }
    }

    // Prints the full DP table showing optimal moves and split values.
    public static void printDPTable(int maxDisks) {
        System.out.println("=".repeat(65));
        System.out.printf("%-8s %-15s %-15s %-12s%n",
                "Disks", "3-Peg Moves", "4-Peg Min DP", "Optimal k");
        System.out.println("-".repeat(65));
        for (int n = 1; n <= maxDisks; n++) {
            System.out.printf("%-8d %-15d %-15d %-12d%n",
                    n, threeP(n), dp4[n], split[n]);
        }
        System.out.println("=".repeat(65));
    }

    // Classical 3-peg Tower of Hanoi (recursive).
    public static void hanoi3(int n, int offset, String src, String dst,
            String aux, boolean print) {
        if (n == 0) return;
        hanoi3(n - 1, offset, src, aux, dst, print);
        moveCount++;
        if (print) {
            System.out.printf("  Move %3d: Disk %2d  |  Peg %s --> Peg %s%n",
                    moveCount, offset + n, src, dst);
        }
        hanoi3(n - 1, offset, aux, dst, src, print);
    }

    /*
     * Uses pre-computed split[n] to determine optimal k.
     * Algorithm for n disks, pegs: src, dst, aux1, aux2:
     *  1. Move top k disks  src  -> aux1  (4 pegs available)
     *  2. Move bottom n-k   src  -> dst   (3 pegs: src, dst, aux2;  aux1 locked)
     *  3. Move top k disks  aux1 -> dst   (4 pegs available)
     */
    public static void hanoi4(int n, int offset, String src, String dst,
                               String aux1, String aux2, boolean print) {
        if (n == 0) return;
        if (n == 1) {
            moveCount++;
            if (print) {
                System.out.printf("  Move %3d: Disk %2d  |  Peg %s --> Peg %s%n",
                        moveCount, offset + 1, src, dst);
            }
            return;
        }

        int k = split[n];   // optimal number of disks to park on aux1

        // Step 1: Move top k disks (disk IDs: offset+1 .. offset+k) to aux1
        hanoi4(k, offset, src, aux1, dst, aux2, print);
 
        // Step 2: Move bottom n-k disks (disk IDs: offset+k+1 .. offset+n) to dst
        //         These are the LARGER disks; offset for this group = offset+k
        hanoi3(n - k, offset + k, src, dst, aux2, print);
 
        // Step 3: Move k disks from aux1 to dst
        hanoi4(k, offset, aux1, dst, src, aux2, print);
    }

    // Convenience wrappers (no offset needed from outside)
    public static void hanoi3(int n, String src, String dst, String aux, boolean print) {
        hanoi3(n, 0, src, dst, aux, print);
    }
    public static void hanoi4(int n, String src, String dst,
                               String aux1, String aux2, boolean print) {
        hanoi4(n, 0, src, dst, aux1, aux2, print);
    }
    
    // Runs a demonstration for a given number of disks.
    public static void runDemo(int n, boolean print) {
        System.out.println("\n" + "=".repeat(65));
        System.out.printf("  DEMO: %d Disk(s), 4 Pegs  |  Pegs: A (src) --> D (dst)%n", n);
        System.out.println("=".repeat(65));
        System.out.printf("  DP predicted minimum moves : %d%n", dp4[n]);
        System.out.printf("  Optimal split k            : %d%n", split[n]);
        System.out.printf("  3-peg comparison (2^n - 1) : %d%n", threeP(n));
        System.out.println("-".repeat(65));

        if (print) System.out.println("  Move sequence:");

        moveCount = 0;
        hanoi4(n, "A", "D", "B", "C", print);

        System.out.println("-".repeat(65));
        System.out.printf("  Actual moves generated: %d  |  DP minimum: %d  |  Match: %s%n",
                moveCount, dp4[n], (moveCount == dp4[n] ? "YES" : "NO"));
        double saving = 100.0 * (threeP(n) - dp4[n]) / threeP(n);
        System.out.printf("  Move reduction vs 3-peg : %.1f%%%n", saving);
        System.out.println("=".repeat(65));
    }
    
    private static int getUserDisks(Scanner sc, int maxDisks) {
        int n = 0;
        while (true) {
            System.out.printf("%nEnter number of disks (1 – %d): ", maxDisks);
            if (sc.hasNextInt()) {
                n = sc.nextInt();
                if (n >= 1 && n <= maxDisks) break;
                System.out.printf("  [Error] Please enter a value between 1 and %d.%n", maxDisks);
            } else {
                System.out.println("  [Error] Invalid input. Please enter a whole number.");
                sc.next(); // discard bad token
            }
        }
        return n;
    }

    private static boolean askYesNo(Scanner sc, String prompt) {
        while (true) {
            System.out.print(prompt + " (y/n): ");
            String ans = sc.next().trim().toLowerCase();
            if (ans.equals("y") || ans.equals("yes")) return true;
            if (ans.equals("n") || ans.equals("no"))  return false;
            System.out.println("  [Error] Please enter y or n.");
        }
    }

    public static void main(String[] args) {

        final int MAX_DISKS = 20;
        buildDPTable(MAX_DISKS);

        System.out.println("\n" + "=".repeat(65));
        System.out.println("  TOWER OF HANOI - 4 PEG FRAME-STEWART DYNAMIC PROGRAMMING");
        System.out.println("=".repeat(65));

        // Print the DP table
        System.out.println("\n[ TABLE 1: DP Optimal Move Counts ]");
        printDPTable(MAX_DISKS);

        Scanner sc = new Scanner(System.in);

        do {
            int n       = getUserDisks(sc, MAX_DISKS);

            // Warn before printing thousands of lines
            boolean print = false;
            if (n <= 12) {
                print = askYesNo(sc, "  Show full move sequence?");
            } else {
                System.out.println("  (Move list suppressed for n > 12 to avoid excessive output.)");
            }

            runDemo(n, print);

        } while (askYesNo(sc, "\nRun another simulation?"));

        System.out.println("\n  Goodbye!");
        sc.close();
    }
}
