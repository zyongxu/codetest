#include <iostream>
#include <vector>
using namespace std;

int min;

void sortedIndices(int len) {
    map<int, int> buffer;
    int intbuf;
    for (int i=0; i<len; i++) {
        cin>>intbuf;
        buffer[intbuf] = i;
    }
    vector<int> order(len,0);
    map<int, int>::iterator mit = buffer.begin();
    int i=0;
    while (mit != buffer.end()) {
        order[i]=mit->second;
        i++;
    }

    vector<int> 

}
