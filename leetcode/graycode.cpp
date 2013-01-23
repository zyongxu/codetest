/* Generate Gray code with n bits
 * Used the symmetric property of gray code
 */

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> grayCode(int n) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        vector<int> ret;
        
        ret.push_back(0);
        int len=1;
        
        for (int i=0; i<n; i++) {
            for (int j=len-1; j>=0; j--) {
                ret.push_back(ret[j]);
            }
            
            len *= 2;
            for (int k=len/2; k<len; k++) {
                ret[k] += (1<<i);
            }
        }
        
        return ret;
    }
};
