/*
 * weird data structure + weird data (index)
 */

class Solution {
public:
    int largestRectangleArea(vector<int> &h) {
        stack<int> p;
        int i = 0, m = 0;
        h.push_back(0);
        while(i < h.size()) {
            if(p.empty() || h[p.top()] <= h[i])
                p.push(i++);
            else {
                int t = p.top();
                p.pop();
                m = max(m, h[t] * (p.empty() ? i : i - p.top() - 1 ));
            }
        }
        return m;
    }
};
