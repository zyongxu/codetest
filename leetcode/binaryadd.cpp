#include <iostream>
#include <cmath>

using namespace std;

void reverseStr(string &a) {
    int i1 = 0;
    int i2 = a.size()-1;
    char temp;
    while(i1<i2) {
        temp = a[i1];
        a[i1] = a[i2];
        a[i2] = temp;
        i1++;
        i2--;
    }
}

string addBinary(string a, string b) {
    char ret_table [] = {'0', '1', '0', '1'};
    char car_table [] = {'0', '0', '1', '1'};
    
    string ret;
    string temp_a, temp_b;
    
    int len;
    int len_a = a.size();
    int len_b = b.size();
    char carry = '0';
    
    reverseStr(a);
    reverseStr(b);
    if (len_a-len_b > 0) { //Must explicitly specify ">0", negative number can pass the check "if(len_a-len_b)"
        temp_a = a;
        temp_b = b;
        len = len_a;
    } else {
        temp_a = b;
        temp_b = a;
        len = len_b;
    }
    
    for (int i = 0; i<abs(len_a-len_b); i++)
        temp_b += '0';
    
    cout << temp_a <<", "<<temp_b<<endl;
    for (int i=0; i<len; i++) {
        ret += ret_table[(temp_a[i]+temp_b[i]+carry-'0'*3)];
        carry = car_table[(temp_a[i]+temp_b[i]+carry-'0'*3)];
    }
    
    if (carry == '1')
    ret += '1';
    
    reverseStr(ret);

    return ret;
}


int main () {
  string str1 = "1";
  string str2 = "111";

  cout << addBinary(str1, str2) << endl;

  return 0;
}
