/*
 *
 */
#include <iostream>
#include <vector>
#include <sstream>
#include <cmath>
#include <iomanip>
using namespace std;

double countOfDay (string &userdata) {
    int len = userdata.size();
    double yescnt = 0;
    for (int i=0; i<len; i++) {
        if (userdata[i]=='1')
            yescnt++;
    }

    return yescnt;
}

string sigma (vector<double> &yescnts) {
    double sqr_exp=0;
    double exp=0;
    for (int i=0; i<7; i++) {
        sqr_exp += (yescnts[i]*yescnts[i]);
        exp += yescnts[i];
    }
    stringstream ss;
    ss<<fixed<<setprecision(4)<<sqrt((sqr_exp-exp*exp/7)/7);

    return ss.str();
}

int main () {
    string buffer;
    vector<double> vy(7,0);
    for (int i=0; i<7; i++) {
        cin>>buffer;
        vy[i]=countOfDay(buffer);
    }

    cout<<sigma(vy)<<endl;
    return 0;
}



