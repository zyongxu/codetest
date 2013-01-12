/* Question:
 * Given an array S of n integers, are there elements a, b, c in S such that a + b + c = 0? 
 * Find all unique triplets in the array which gives the sum of zero.
 *
 * Note:
 * Elements in a triplet (a,b,c) must be in non-descending order. (ie, a ≤ b ≤ c)
 * The solution set must not contain duplicate triplets.
 *    For example, given array S = {-1 0 1 2 -1 -4},
 *
 *    A solution set is:
 *    (-1, 0, 1)
 *    (-1, -1, 2)
 */



#include <iostream>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int> > threeSum(vector<int> &num) {
    sort(num.begin(), num.end());
    set<vector<int> > vec_buf;
    vector<vector<int> > ret;
    int len = num.size();
    for (int i=0; i<len-2; i++) {
        int j = i+1;
        int k = len-1;
        while (j<k) {
            if (num[j]+num[k] < -num[i])
                j++;
            else if (num[j]+num[k] > -num[i])
                k--;
            else {
                vector<int> temp;
                cout << i <<": "<< num[i] << endl;
                temp.push_back(num[i]);
                cout << j <<": "<< num[j] << endl;
                temp.push_back(num[j]);
                cout << k <<": "<< num[k] << endl;
                temp.push_back(num[k]);
                vec_buf.insert(temp);
                j++;
                k--;
            }
        }
    }
    
    set<vector<int> >::iterator sit = vec_buf.begin();
    for(; sit != vec_buf.end(); sit++)
        ret.push_back(*sit);
        
    return ret;
}


int main(int argc, char *argv[]) {
  vector<int> num;
  num.push_back(1);
  num.push_back(2);
  num.push_back(-2);
  num.push_back(-1);
  threeSum(num);
  
  return 0;
}
