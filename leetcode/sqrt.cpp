#include <iostream>

using namespace std;

int sqrt(int x) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    int l=0;
    int r=x;
    while (l<r) {
        cout<<"l: "<<l<<" r: "<<r<<endl;
        int m = (l+r)/2;
        if (m*m>x) {
            r=m-1;
        } else {
            l=m+1;
        }
    }
    
    return l;
}

int main() {
    cout<<sqrt(4)<<endl;

    return 0;
}
