package io.github.zyongxu.solver;

import java.util.concurrent.Callable;

/**
 * <p>A interface that creates a {@code Runnable} to work out the give problem</p>
 *
 * @author yx
 * @since 4/9/16
 */
public abstract class SolutionFactory {
    class Solution {
        private final int index;
        private final String answer;

        // package-private
        Solution(int index, String answer) {
            this.index = index;
            this.answer = answer;
        }

        int getIndex() {
            return index;
        }

        String getAnswer() {
            return answer;
        }
    }

    Callable<Solution> solve(int index, String problem) {
        System.out.format("solving problem #%d: %s\n", index, problem);

        return () -> new Solution(index, workOut(problem));
    }

    /**
     * <p>Override this method with the actual code that solves the problem</p>
     *
     * @param problem the problem to solve
     * @return solution in a String
     */
    protected abstract String workOut(String problem);
}
