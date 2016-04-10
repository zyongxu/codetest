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
    private final String inputFilename;
    private final ExecutorService caseSolvers;
    private final List<Future<SolutionFactory.Solution>> solutions = new ArrayList<>();

    public enum InputType {
        Small, Large
    }

    public ConcurrentSolver(int numOfThreads, InputType inputType) throws IllegalArgumentException {
        this.caseSolvers = Executors.newFixedThreadPool(numOfThreads);
        switch (inputType) {
            case Small:
                this.inputFilename = "A-small-practice.in";
                break;
            case Large:
                this.inputFilename = "A-large-practice.in";
                break;
            default:
                throw new IllegalArgumentException("invalid inputType");
        }
    }

    /**
     * <p>
     * Solve all problems defined in the {@code workingDir/input.txt} concurrently,
     * then output solutions to {@code workingDir/output.txt}.
     * The input file should be in the "google code jam format"
     * </p>
     *
     * @param workingDir path to the working directory that contains {@code input.txt}
     * @throws FileNotFoundException
     */
    public void solve(String workingDir, SolutionFactory solutionFactory) throws IOException {
        BufferedReader br = new BufferedReader(new FileReader(workingDir + "/" + inputFilename));
        int numOfCases = Integer.parseInt(br.readLine());
        System.out.format("Found %d test cases\n", numOfCases);

        for (int i = 0; i < numOfCases; i++) {
            final String content = br.readLine();
            Future<SolutionFactory.Solution> traceableSolution =
                    caseSolvers.submit(solutionFactory.solve(i + 1, content));
            solutions.add(traceableSolution);
        }

        System.out.println("All problems are submitted to solver, waiting to merge results");
        // stop accepting new submissions while waiting for the solver to work out all
        // submitted cases
        caseSolvers.shutdown();

        try {
            mergeSolutions(workingDir);
        } catch (ExecutionException | InterruptedException e) {
            e.printStackTrace();
        }
        System.out.println("Done!");
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

            bw.write(String.format("Case #%d: %s\n", solution.getIndex(), solution.getAnswer()));
            System.out.printf("case #%d solved\n", solution.getIndex());
        }

        bw.close();
    }
}
