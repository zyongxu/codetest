package io.github.zyongxu.solver;

import java.io.*;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.*;

/**
 * <p>Read input from a file; concurrently solve all test cases; then merge and
 * output result to a output file for submission</p>
 *
 * @author yx
 * @since 4/9/16
 */
public class ConcurrentSolver {
    private int numOfCases;
    private final ExecutorService caseSolvers;
    private final List<Future<SolutionFactory.Solution>> solutions = new ArrayList<>();

    public ConcurrentSolver(int numOfThreads) {
        this.caseSolvers = Executors.newFixedThreadPool(numOfThreads);
    }

    /**
     * <p>
     * Solve all problems defined in the {@code workDir/input.txt} concurrently,
     * then output solutions to {@code workDir/output.txt}.
     * The input file should be in the "google code jam format"
     * </p>
     *
     * @param workDir path to the working directory
     * @throws FileNotFoundException
     */
    public void solve(String workDir, SolutionFactory solutionFactory) throws IOException {
        BufferedReader br = new BufferedReader(new FileReader(workDir + "/input.txt"));
        numOfCases = Integer.parseInt(br.readLine());
        for (int i = 0; i < numOfCases; i++) {
            final String content = br.readLine();
            Future<SolutionFactory.Solution> tracableSolution =
                    caseSolvers.submit(solutionFactory.solve(i + 1, content));
            solutions.add(tracableSolution);
        }

        try {
            mergeSolutions(workDir);
        } catch (ExecutionException e) {
            e.printStackTrace();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

    private void mergeSolutions(String workDir) throws IOException, ExecutionException, InterruptedException {
        final BufferedWriter bw = new BufferedWriter(new FileWriter(workDir + "/output.txt"));

        for (Future<SolutionFactory.Solution> solutionFut : solutions) {
            SolutionFactory.Solution solution;
            try {
                solution = solutionFut.get(1, TimeUnit.MINUTES);
            } catch (TimeoutException e) {
                e.printStackTrace();
                break;
            }

            bw.write("Case " + solution.getIndex() + ": " + solution.getAnswer());
        }
    }
}
