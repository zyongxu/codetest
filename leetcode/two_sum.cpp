#include <iostream>
#include <set>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

vector<int> twoSum(vector<int> &numbers, int target) {
    int len = numbers.size();
    multimap<int, int> buf;
    for (int i=0; i<len; i++) {
        buf.insert(make_pair(numbers[i], i+1));
    }
    auto i=buf.begin();
    auto j=buf.rbegin();
    while (i->first <= j->first) {
        if (i->first + j->first < target)
            ++i;
        else if (i->first + j->first > target)
            ++j;
        else
            return {min(i->second, j->second), max(i->second, j->second)};
    }
    
    return vector<int>();
}

int main(int argc, char *argv[]) {
  vector<int> num{0,4,3,0};
  auto ret = twoSum(num, 0);
  cout << ret[0] << ", " << ret[1] << endl;
  
  return 0;
}
