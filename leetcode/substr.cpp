/*
 * Brute Force way (cannot pass large test):
 *
 * class Solution {
 * public:
 *     int numDistinct(string S, string T) {
 *         if (T.empty())
 *             return 1;
 *         else if (S.empty())
 *             return 0;
 *         int lenS = S.size();
 *         
 *         int num = 0;
 *         for (int i=0; i<lenS; i++) {
 *             if (S[i] == T[0]) {
 *                 num += numDistinct(S.substr(i+1), T.substr(1));
 *             }
 *         }
 *         return num;
 *     }
 * };
 */

#include <iostream>
#include <vector>
#include <string>

using namespace std;

int numDistinct(string S, string T) {
    int lenS = S.size();
    int lenT = T.size();
    
    vector<vector<int> > dptable(lenS+1, vector<int>(lenT+1, 0));
    
    dptable[0][0] = 1;
    
    for (int i=1; i<=lenS; i++) {
        for (int j=1; j<=lenT; j++) {
            if (S[i] == T[j]) {
                cout << S[i] <<" = "<<T[j]<<endl;
                dptable[i][j] = dptable[i-1][j-1]
                            + dptable[i-1][j];
            } else {
                cout << "of course!"<<endl;
                dptable[i][j] = dptable[i-1][j];
            }
        }
    }
    
    return dptable[lenS][lenT];
}

int main() {
    cout << numDistinct("b", "a") << endl;
    return 0;
}
