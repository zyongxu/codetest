#include <vector>
#include <set>
#include <iostream>
#include <utility>
using namespace std;

    int lengthOfLongestSubstring(string s) {
        auto len = s.size();
        vector<vector<pair<bool, set<char>>>> dp(len, vector<pair<bool, set<char>>>(len, pair<bool, set<char>>()));
        for (int i=0; i<len; i++) {
            dp[i][i] = make_pair(true, set<char>{s[i]});
        }
        
        int ret = 1;
        for (int i=0; i<len; i++) {
            for (int j=i+1; j<len; j++) {
                dp[i][j] = dp[i][j-1];
                if (dp[i][j].first) {
                    if (dp[i][j].second.count(s[j]) == 0) {
                        dp[i][j].first = true;
                        dp[i][j].second.insert(s[j]);
                        if (j-i+1 > ret)
                            ret = j-i+1;
                    } else {
                        dp[i][j].first = false;
                    }
                }
            }
        }
        return ret;
    }

int main() {
    cout << lengthOfLongestSubstring("wlrbbmqbhcdarzowkkyhiddqscdxrjmowfrxsjybldbefsarcbynecdyggxxpklorellnmpapqfwkhopkmco") << endl;
    return 0;
}
