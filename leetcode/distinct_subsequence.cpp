/*
 * Distinct Subsequences
 * Given a string S and a string T, count the number of distinct subsequences of T in S.
 * 
 * A subsequence of a string is a new string which is formed from the original
 * string by deleting some (can be none) of the characters without disturbing the
 * relative positions of the remaining characters. (ie, "ACE" is a subsequence of
 * "ABCDE" while "AEC" is not).
 * 
 * Here is an example:
 * S = "rabbbit", T = "rabbit"
 * 
 * Return 3.
 */

class Solution {
public:
    int numDistinct(string S, string T) {
        int lenS = S.size();
        int lenT = T.size();
        /* The dp[i][j] is the number of distinct substrs of T[0..j] in S[0..i]
         */
        vector<vector<int> > dp(lenS+1, vector<int> (lenT+1));
        dp[0][0]=1;
        for (int i=1; i<lenS; i++)
            dp[i][0]=1;
        
        for (int i=1; i<=lenS; i++) {
            for (int j=1; j<=lenT; j++) {
                if (S[i-1] == T[j-1])
                    dp[i][j]=dp[i-1][j-1]+dp[i-1][j];
                else
                    dp[i][j]=dp[i-1][j];
            }
        }
        
        return dp[lenS][lenT];
    }
};
