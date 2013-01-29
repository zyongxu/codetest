/*
 * Next Permutation

 * Implement next permutation, which rearranges numbers into the lexicographically next greater permutation of numbers.
 * 
 * If such arrangement is not possible, it must rearrange it as the lowest possible order (ie, sorted in ascending order).
 * 
 * The replacement must be in-place, do not allocate extra memory.
 * 
 * Here are some examples. Inputs are in the left-hand column and its corresponding outputs are in the right-hand column.
 * 
 * 1,2,3 → 1,3,2
 * 3,2,1 → 1,2,3
 * 1,1,5 → 1,5,1
 */


class Solution {
public:
    int trap(int A[], int n) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if (n<1)
            return 0;

        stack<int> s;
        int water = 0;
        int i=0;
        while (i<n) {
            if (s.empty() || A[i]<=A[s.top()]) {
                s.push(i);
                i++;
            } else if (A[i]>A[s.top()]) {
                int temp = s.top();
                s.pop();
                if (!s.empty())
                    water += (min(A[i], A[s.top()])-A[temp]) * (i-s.top()-1);
            }
        }
        
        return water;
    }
};
