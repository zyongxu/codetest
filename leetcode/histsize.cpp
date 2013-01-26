/* Find the largest Rectangle under historgram
 * When need to track a lot of info and a vector is not an option,
 * try queue or stack!
 */

class Solution {
public:
    int largestRectangleArea(vector<int> &height) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        stack<int> idxstack;
        height.push_back(0);
        int len = height.size();

        int i=0;
        int maxsize = 0;
        while (i<len) {
            if (idxstack.empty() || height[idxstack.top()]<height[i]) {
                idxstack.push(i);
                i++;
            } else {
                int j = idxstack.top();
                idxstack.pop();
                int s = height[j] * (idxstack.empty() ? i : i-1-idxstack.top());
                maxsize = max(s, maxsize);
            }
        }
        return maxsize;
    }
};
