/*
 * N-Queens
 * 
 * The n-queens puzzle is the problem of placing n queens on an n*n chessboard
 * such that no two queens attack each other.
 * 
 * 
 * 
 * Given an integer n, return all distinct solutions to the n-queens puzzle.
 * 
 * Each solution contains a distinct board configuration of the n-queens'
 * placement, where 'Q' and '.' both indicate a queen and an empty space
 * respectively.
 * 
 * For example,
 * There exist two distinct solutions to the 4-queens puzzle:
 * 
 * [
 *  [".Q..",  // Solution 1
 *   "...Q",
 *   "Q...",
 *   "..Q."],
 * 
 *  ["..Q.",  // Solution 2
 *   "Q...",
 *   "...Q",
 *   ".Q.."]
 * ]
 *
 * Sol: backtack. It's a little bit less efficint, but straight forward to use a 
 * bruto-force isSafe() check
 */


class Solution {
public:
    vector<vector<string> >queens;
    bool isSafe(int qnum, int qpos, vector<int> &buf) {
        int len = buf.size();
        for (int i=0; i<len; i++) {
            if (buf[i] == qpos)
                return false;
            else if (buf[i] + qnum - i == qpos)
                return false;
            else if (buf[i] - qnum + i == qpos)
                return false;
        }
        return true;
    }
    
    void solve(int qnum, int N, vector<int> buf) {
        if (qnum == N) {
            vector<string> ret;
            for (int i=0; i<N; i++) {
                string sret;
                for (int j=0; j<N; j++) {
                    if (j != buf[i])
                        sret += ".";
                    else
                        sret += "Q";
                }
                ret.push_back(sret);
            }
            queens.push_back(ret);
            return;
        }
        
        for (int i=0; i<N; i++) {
            if (isSafe(qnum, i, buf)) {
                vector<int> temp (buf);
                temp.push_back(i);
                solve(qnum+1, N, temp);
            }
        }
    }
    
    vector<vector<string> > solveNQueens(int n) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        queens.clear();
        solve(0, n, vector<int>());
        
        return queens;
    }
};
