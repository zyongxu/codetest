#include <vector>
#include <unordered_set>
#include <iostream>
using namespace std;

class Solution {
public:
    vector<string> wordBreak(string s, unordered_set<string> &dict) {
        int len = s.size();
        vector<vector<string> > dp(len, vector<string>());

        for (int i=len-1; i>=0; i--) {
            for (int j=i; j<len; j++) {
                if (dict.count(s.substr(i, j-i+1)) > 0) {
                    //cout << s.substr(i, j-i+1) << "@" << j << endl;
                    if (j == len - 1) {
                        //cout << "push @" << j << ": "<< s.substr(i, j-i+1) << endl;
                        dp[i].push_back(s.substr(i, j-i+1));
                    } else if (dp[j+1].size() > 0) {
                        for (auto& str : dp[j+1]) {
                            //cout << "push " << s.substr(i, j-i+1) + " " + str << endl;
                            dp[i].push_back(s.substr(i, j-i+1) + " " + str);
                        }
                    }
                }
            }
        }
        return dp[0];
    }
};

int main() {
    Solution sl;
    unordered_set<string> ws = {"cat", "cats", "and", "sand", "dog"};
    for (auto& str : sl.wordBreak("catsanddog", ws))
        cout << str << endl;
    return 0;
}
