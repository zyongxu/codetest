#include <iostream>
#include <vector>

using namespace std;

bool isInterleave(string s1, string s2, string s3) {
  // index 0 is a santigard for empty string
  vector<vector<bool> > dpmap(s1.size()+1, vector<bool> (s2.size()+1));
  
  dpmap[0][0]=true;
  int s1len = s1.size();
  int s2len = s2.size();
  
  if (s1len+s2len != s3.size())
      return false;

  for(int i=1; i<=s1len; i++) {
      if(s1[i-1] == s3[i-1])
          dpmap[i][0] = true;
      else
          break;
  }
  
  for (int i=1; i<=s2len; i++) {
      if(s2[i-1] == s3[i-1])
          dpmap[0][i] = true;
      else
          break;
  }
  
  // Think about the func before implement!!!!!!!
  for (int m=1; m<=s1len; m++) {
      for (int n=1; n<=s2len; n++) {
          bool t1, t2;
          if (s1[m-1] == s3[m+n-1])
              dpmap[m][n] = dpmap[m-1][n];
          if (s2[n-1] == s3[m+n-1])
              dpmap[m][n] = dpmap[m][n-1] | dpmap[m][n];
      }
  }
  return dpmap[s1len][s2len];
}

int main() {
  cout << isInterleave("aabc","abad","aabadabc") << endl;
  return 0;
}
