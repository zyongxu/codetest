/*
 * Given a collection of integers that might contain duplicates, S, 
 * return all possible subsets.
 * 
 * Note:
 * Elements in a subset must be in non-descending order.
 * The solution set must not contain duplicate subsets.
 * For example,
 * If S = [1,2,2], a solution is:
 * 
 * [
 *   [2],
 *   [1],
 *   [1,2,2],
 *   [2,2],
 *   [1,2],
 *   []
 * ]
 * 
 * Running time on large set: 56ms
 */

class Solution {
private:
    
public:
    vector<vector<int> > subsetsWithDup(vector<int> &S) {
        int Slen = S.size();
        map<int, int> elems;
        
        for(int i=0; i<Slen; i++) {
            elems[S[i]] += 1;
        }
        vector<vector<int> > ret;
        
        map<int, int>::iterator mit = elems.begin();
        
        while (mit != elems.end()) {
            int len = ret.size();

            for (int i=0; i<len; i++) {
                for (int j=1; j<=mit->second; j++) {
                    vector<int> temp(ret[i]);
                    for (int k=0; k<j; k++) {
                        temp.push_back(mit->first);
                    }
                    ret.push_back(temp);
                }
            }
            
            for (int i=1; i<=mit->second; i++) {
                ret.push_back(vector<int>(i, mit->first));
            }
            mit++;
        }
        ret.push_back(vector<int>());
        return ret;
    }
};
