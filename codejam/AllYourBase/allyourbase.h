#ifndef ALLYOURBASE_H_
#define ALLYOURBASE_H_

#include "base.h"
#include <vector>
#include <fstream>
using namespace std;

class Solution : public BaseSolu {
public:
    long long run (ifstream &in) {
        vector<int> dict(256, -1);
        string buf;
        in>>buf;
        int len = buf.size();
        dict[buf[0]]=1;
        int curi=1;
        while (curi<len) {
            if (buf[curi] != buf[0]) {
                dict[buf[curi]]=0;
                curi++;
                break;
            }
            curi++;
        }
        int cur =2;
        for (int i=curi; i<len; i++) {
            if (dict[buf[i]]<0) {
                dict[buf[i]]=cur;
                cur++;
            }
        }
        long long ret = 0;
        for (int i=0; i<len; i++) {
            ret *= (long long)cur;
            ret += (long long)dict[buf[i]];
        }
        return ret;
    }
};


#endif
