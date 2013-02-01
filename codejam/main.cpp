#include <iostream>
#include <fstream>
#include <ctime>
//#include "RopeIntranet/ropeintranet.h"
#include "FileFixIt/filefixit.h"
using namespace std;

int main (int argc, char *argv[]) {
    clock_t ct;
    ifstream in(argv[1]);
    if (!in) {
        cout<<"Wrong file name!"<<endl;
        return 1;
    }
    ofstream out("result.out");

    Solution sol;
    sol.prepare(in);

    ct=clock();
    cout<<"Number of test cases: "<<sol.nu_cases<<endl;
    for (int i=0; i<sol.nu_cases; i++) {
        sol.casePrepare(in);
        out<<"Case #"<<i+1<<": "<<sol.run(in)<<endl;
    }
    ct=clock() - ct;

    in.close();
    out.close();
    cout<<"Done! running time: "<<((float) ct)/CLOCKS_PER_SEC*1000<<" milisec"<<endl;
    return 0;
}
