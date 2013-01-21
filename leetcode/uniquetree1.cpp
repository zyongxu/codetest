/* find the number of unique tree structures with n nodes
 * recursion + DP
 */

class Solution {
public:
    map<int, int> nums;
    
    Solution() {
        nums[0]=1; // 0 node has 0 structures
        nums[1]=1; // 1 node has 1 structure
    }
    
    int numTrees(int n) {
        if (nums.find(n) != nums.end())
            return nums[n];
        
        int num = 0;
        for (int i=0; i<ceil(n/2); i++)
            num += numTrees(i)*numTrees(n-1-i);
        
        num *= 2;
        
        if(n % 2 == 1)
            num += pow(numTrees((n-1)/2), 2);
        
        nums[n] = num;
        
        return num;
    }
};
