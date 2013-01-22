#include <string>
#include <iostream>
#include <vector>

using namespace std;

void findIp(string cur, string s, int numf, vector<string> &ret) {
    if (numf == 4 && s.size() == 0) {
        ret.push_back(cur);
        return;
    } else if (numf<4) {
        char temp = s[0];
        int val = temp-'0';
        if(numf>0)
            cur+=".";
        cur+=s[0];
        
        if (val == 0)
            findIp(cur, s.substr(1), numf+1, ret);
        else {
            int cnt = 1;
            while (val<256) {
                if (s.size()<cnt)
                    break;
                findIp(cur, s.substr(cnt), numf+1, ret);
                // new str
                cur +=s[cnt];
                val = val*10 + s[cnt]-'0';
                cnt++;
            }
        }
    }
}

vector<string> restoreIpAddresses(string s) {
    vector<string> ret;
    findIp("", s, 0, ret);
    
    return ret;
}

int main() {
    string test = "1111";
    restoreIpAddresses(test);
    return 0;
}
