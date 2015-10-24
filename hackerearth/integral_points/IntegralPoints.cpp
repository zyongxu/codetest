#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

long long GCD(long long a, long long b) {
    while (b != 0) {
        long long r = a % b;
        a = b;
        b = r;
    }
    return a;
}

/*
 * Calculate the area of given triangle * 2
 */
long long calcDoubleArea(long long Ax, long long Ay, long long Bx, long long By, long long Cx, long long Cy) {
    return abs(Ax*(By-Cy) + Bx*(Cy - Ay) + Cx*(Ay-By));
}

/*
 * Calcuate the # of points on a line, including A(ax, ay) but excluding B(bx, by)
 */
long long numOfPtsOnLine(long long ax, long long ay, long long bx, long long by) {
    return GCD(abs(ax-bx), abs(ay-by));    
}

int numOfInternalPts(long long ax, long long ay, long long bx, long long by, long long cx, long long cy) {
    long long doubleArea = calcDoubleArea(ax, ay, bx, by, cx, cy);
    return  (doubleArea - numOfPtsOnLine(ax, ay, bx, by) -
                          numOfPtsOnLine(ax, ay, cx, cy) -
                          numOfPtsOnLine(bx, by, cx, cy)) / 2
            + 1;
}

int main() {
    int T;
    cin >> T;
    
    vector<long long> results;
    for (int i=0; i<T; i++) {
        long long ax, ay, bx, by, cx, cy;
        cin >> ax >> ay >> bx >> by >> cx >> cy;
        results.push_back(numOfInternalPts(ax, ay, bx, by, cx, cy));
    }
    
    for (const auto& r : results)
        cout << r << endl;
    
    return 0;
}
