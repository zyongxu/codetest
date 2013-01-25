/*
 * When doing back tracking (e.g. doing experiment of 
 * whether each decsion leads to a valid answer), DO NOT
 * add too much judgment during the process! Add judgments
 * when then process is done, and if it's not a valid result, 
 * just throw it away
 */


#include <vector>
#include <iostream>
#include <string>

using namespace std;

vector<string> ips;

void findIp(string s, vector<string> tempIp) {
    if (tempIp.size() == 4 && s.empty()) {
        cout << "found an valid one"<<endl;
        for (int i=0; i< tempIp.size(); i++) {
            cout << tempIp[i]<<" ";
        }
        cout << endl;
        string temp = tempIp[0]+"."
                     +tempIp[1]+"."
                     +tempIp[2]+"."
                     +tempIp[3];
        ips.push_back(temp);
        return;
    } else if (tempIp.size() >=4 || s.empty()) {
        return;
    }
    
    int idx = 0;
    int value = s[idx]-'0';
    if (value == 0) {
        tempIp.push_back(s.substr(0,1));
        findIp(s.substr(1), tempIp);
        return;
    }
    while (value<256 && idx<s.size()) {
        idx++;
        vector<string> newIp(tempIp);
        newIp.push_back(s.substr(0, idx));
        findIp(s.substr(idx), newIp);
        value = value*10+s[idx]-'0';
    }
}

vector<string> restoreIpAddresses(string s) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    if(s.size()<4)
        return vector<string> ();
    
    findIp(s, vector<string>());
    return ips;
    
}

int main () {
    vector<string> ret = restoreIpAddresses("1111");
    for (int i=0; i<ret.size(); i++)
        cout << ret[i] << endl;
    return 0;
}
