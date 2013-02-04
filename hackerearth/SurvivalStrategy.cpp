/*
 * N people stand around a circle, every other died
 * who is the only one survived at last?
 *
 * Solu: There is a pattern in this question, so 
 * this question is actually meaningless. Unless
 * coming up with some smart solu that doesn't 
 * relay on the pattern
 *
 * The pattern:
 * number of people     1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19  
 * position of survivor 1 1 3 1 3 5 7 1 3  5  7  9 11 13 15  1  3  5  7
 *
 */

#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int survivor(int peopleNum) {
    int exp2 = log(peopleNum)/log(2);
    int base = pow((float) 2, exp2);
    return 1+(peopleNum-base)*2;
}

int main () {
    int T;
    cin>>T;
    int n;
    for (int i=0; i<T; i++) {
        cin>>n;
        cout<<survivor(n)<<endl;
    }

    return 0;
}
