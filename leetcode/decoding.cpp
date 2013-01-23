/* Decode Ways
 * A message containing letters from A-Z is being encoded to 
 * numbers using the following mapping:
 * 
 * 'A' -> 1
 * 'B' -> 2
 * ...
 * 'Z' -> 26
 * Given an encoded message containing digits,a
 * determine the total number of ways to decode it.
 * 
 * For example,
 * Given encoded message "12", it could be decoded as "AB" (1 2) or "L" (12).
 * 
 * The number of ways decoding "12" is 2.
 *
 * Solution: backtracking + DP 
 * bt idea:
 *   if (valid result): return result
 *   else if (not promising): return
 *   else if (promising): bt(substr)
 */

#include <iostream>
#include <map>

using namespace std;

class Solution {
public:
    map<string, int> dptable;
    int findDecoding(string s) {
        if (dptable.find(s) != dptable.end()) {
            return dptable[s];
        }
        
        if (s.empty()) {
            return 1;
        } else if (s[0] == '0') {
            dptable[s] = 0;
            return 0;
        } else {
            int numWays = findDecoding(s.substr(1));
            if (s.size()>1) {
                int num = (s[0]-'0')*10 +s[1]-'0';
                if (num<27)
                    numWays += findDecoding(s.substr(2));
            }
            dptable[s] = numWays;
            return numWays;
        }
    }
    
    int numDecodings(string s) {
        if(s.empty())
            return 0;
        return findDecoding(s);
    }
};

int main() {
    Solution test;
    cout<< test.numDecodings(string("11")) <<endl;

    return 0;
}
