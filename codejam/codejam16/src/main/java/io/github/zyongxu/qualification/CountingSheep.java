package io.github.zyongxu.qualification;

import io.github.zyongxu.solver.ConcurrentSolver;
import io.github.zyongxu.solver.SolutionFactory;

import java.io.IOException;
import java.util.HashSet;
import java.util.Set;

/**
 * 2016 Qualification round - Question 1: https://code.google.com/codejam/contest/6254486/dashboard
 */
public class CountingSheep extends SolutionFactory {
    private static final String INSOMNIA = "INSOMNIA";
    private static final int ITER_LIMIT = 1000000;

    @Override
    public String workOut(String problem) {
        long N = Long.parseLong(problem);
        if (N == 0)
            return INSOMNIA;

        final Set<Long> digits = new HashSet<>();

        for (int i = 1; i < ITER_LIMIT; i++) {
            long iN = i * N;
            final long initValue = iN;
            while (iN > 0) {
                digits.add(iN % 10);
                iN /= 10;
            }

            if (digits.size() == 10) {
                return Long.toString(initValue);
            }
        }

        System.err.format("Max number of iteration (%d) has reached, return %s", ITER_LIMIT, INSOMNIA);
        return INSOMNIA;
    }

    public static void main(String[] args) throws IOException {
        if (args.length != 1) {
            System.err.println("Usage: java -cp codejam16.jar CountingSheep <working dir>");
            return;
        }

        final String workingDir = args[0];
        final ConcurrentSolver solver = new ConcurrentSolver(3, ConcurrentSolver.InputType.Large);
        solver.solve(workingDir, new CountingSheep());
    }
}
