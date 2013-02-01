#ifndef ROPE_H_
#define ROPE_H_

#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
private:

public:
    int nu_cases;
    void prepare(ifstream &in) {
        in>>nu_cases;
    }

    int run(ifstream &in) {
        int N, l, r;
        in>>N;
        map<int, int> ropes;
        vector<int> rbuilding;
        for (int j=0; j<N; j++) {
            in>>l>>r;
            ropes[l]=r;
            rbuilding.push_back(r);
        }
        sort(rbuilding.begin(), rbuilding.end());
        map<int, int>::iterator mit = ropes.begin();
        vector<int>::iterator vit;

        int ret = 0;
        for (; mit != ropes.end(); mit++) {
            vit = find(rbuilding.begin(), rbuilding.end(), mit->second);
            ret += (vit-rbuilding.begin());
            rbuilding.erase(vit);
        }
        return ret;
    }
};

#endif
