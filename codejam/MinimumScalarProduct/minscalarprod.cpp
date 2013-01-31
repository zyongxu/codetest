#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
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

    for (int j=0; j<N; j++) {
        int n;
        in>>n;
        vector<long long> s1, s2;
        for (int i=0; i<n; i++) {
            long long temp;
            in>>temp;
            s1.push_back(temp);
        }
        for (int i=0; i<n; i++) {
            long long temp;
            in>>temp;
            s2.push_back(temp);
        }

        sort(s1.begin(), s1.end());
        sort(s2.begin(), s2.end());
        long long ret=0;
        for (int i=0; i<n; i++) {
            // IMPORTANT: the (long long) conversion is
            // NECESSARY here! Otherwise, since s1[] and s2[]
            // are int, the result my OVERFLOW even if ret
            // is long long itself
            ret += (long long) (s1[i]*s2[n-1-i]);
        }
        out <<"Case #"<<j+1<<": "<< ret << endl;
    }

    in.close();
    out.close();

    return 0;
}
