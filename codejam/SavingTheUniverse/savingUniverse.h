#ifndef SAVEUNI_H
#define SAVEUNI_H

#include "base.h"
#include <iostream>
#include <fstream>
#include <set>
using namespace std;

class Solution:public BaseSolu {
public:
    int run (ifstream &in) {
        int S, Q;
        in>>S;
        set<string> engines;
        string name;
        getline(in, name);
        for (int i=0; i<S; i++) {
            getline(in, name);
            engines.insert(name);
        }

        set<string> temp(engines);
        in>>Q;
        getline(in, name);
        int ret=0;
        for (int i=0; i<Q; i++) {
            getline(in, name);
            if (temp.find(name) != temp.end()) {
                temp.erase(name);
            }
            if (temp.empty()) {
                ret++;
                temp = engines;
            }
        }

        return ret;
    }
};

#endif
