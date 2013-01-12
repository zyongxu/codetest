#include <iostream>
#include <map>
#include <vector>

using namespace std;

string sortStr(string str) {
  int len = str.size();
  for (int i=1; i<len; i++) {
    int j=i;
    char temp = str[i];
    while (j>0) {
      if (str[j-1] > temp) {
        str[j] = str[j-1];
        j--;
      }
      else
        break;
    }
    str[j] = temp;
  }
  return str;
}
  
  
vector<string> anagrams(vector<string> &strs) {
  map<string, vector<string> > strtable;
  vector<string> ret;
  
  int vlen = strs.size();
  for (int i=0; i<vlen; i++) {
    strtable[sortStr(strs[i])].push_back(strs[i]);
  }
  
  map<string, vector<string> >::iterator vit = strtable.begin();
  
  for(;vit != strtable.end(); vit++) {
    cout<<vit->first<<": "<<endl;
    for (int i=0; i<vit->second.size(); i++) {
      cout<<"   "<<vit->second[i]<<endl;
    }
    if (vit->second.size() > 1) {
      ret.insert(ret.end(), vit->second.begin(), vit->second.end());
    }
  }
  
  return ret;
}


int main() {
  vector<string> test;
  test.push_back("ape");
  test.push_back("pea");
  test.push_back("tax");
  
  vector<string> ret(anagrams(test));
  
  for (int i=0; i<ret.size(); i++) {
    cout<<ret[i]<<endl;
  }

  return 0;
}
