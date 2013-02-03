#include <iostream>
#include <string>

using namespace std;

string shift (string instr, int n) {
  int len = instr.size();
  string ret(instr);
  for (int i=0; i<len; i++) 
    ret[(i+n)%len] = instr[i];

  return ret;
}

int main(int argc, char *argv[]) {
  string input(argv[1]);
  cout << shift(input, 2) << endl;
  return 0;
}
