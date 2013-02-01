#ifndef BASE_H_
#define BASE_H_

#include <fstream>
using namespace std;

class BaseSolu {
public:
    int nu_cases;
    virtual void prepare(ifstream &in) {
        in>>nu_cases;
    }

    virtual void casePrepare(ifstream &in) {}
};

#endif
