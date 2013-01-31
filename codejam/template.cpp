#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

int main (int argc, char *argv[]) {
    ifstream in(argv[1]);
    if (!in) {
        cout<<"Wrong file name!"<<endl;
        return 1;
    }
    ofstream out("output");

    int N;
    in>>N;

    for (int i=0; i<N; i++) {
        out<<"Case #:"<<i<<": "<<"<ANSWER i>"<<endl;
    }

    in.close();
    out.close();

    return 0;
}
