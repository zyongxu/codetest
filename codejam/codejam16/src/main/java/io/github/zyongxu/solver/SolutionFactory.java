package io.github.zyongxu.solver;

import java.util.concurrent.Callable;

/**
 * <p>A interface that creates a {@code Runnable} to work out the give problem</p>
 *
 * @author yx
 * @since 4/9/16
 */
public interface SolutionFactory {
    class Solution {
        private final int index;
        private final String answer;

        public Solution(int index, String answer) {
            this.index = index;
            this.answer = answer;
        }

        public int getIndex() {
            return index;
        }

        public String getAnswer() {
            return answer;
        }
    }

    Callable<Solution> solve(int index, String problem);
}
