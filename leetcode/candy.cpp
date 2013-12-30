/*
 * Split the requirements into two parts which are much easier to handle
 * From: "Children with a higher rating get more candies than their neighbors."
 * To: 1. Children with a higher rating than their left neighbor get more candies than that neighbor.
 *     2. Children with a higher rating than their right neighbor get more candies than that neighbor.
 */
#include <vector>
#include <iostream>
using namespace std;

class Solution {
public:
    int candy(vector<int> &ratings) {
        int len = ratings.size();
        vector<int> ret(len, 1);
        int cnt = 0;
        for (int i=1; i<len; i++) {
            if (ratings[i] > ratings[i-1])
                ret[i] = ret[i-1]+1;
            cnt += ret[i];
        }

        cnt += ret[0];

        for (int i=len-2; i>=0; i--) {
            if (ratings[i] > ratings[i+1]) {
                if (ret[i] < ret[i+1]+1) {
                    cnt += (ret[i+1]+1-ret[i]);
                    ret[i] = ret[i+1]+1;
                }
            }
        }

        return cnt;
    }
};

int main() {
    Solution s;
    vector<int> v = {0};
    cout << s.candy(v) << endl;

    return 0;
}
