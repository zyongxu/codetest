#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <map>

using namespace std;

void findItems(vector<int> &items, int C, int I, ofstream &of) {
    multimap<int, int> itemsmap;
    for (int i=0; i<I; i++)
        itemsmap.insert(pair<int, int>(items[i], i));

    multimap<int, int>::iterator it1, it2;
    it1 = itemsmap.begin();
    it2 = itemsmap.end();
    it2--;
    while (it1 != it2) {
        if (it1->first+it2->first==C) {
            of<<min(it1->second, it2->second)+1<<" "<<max(it1->second, it2->second)+1<<endl;
            break;
        }
        else if (it1->first+it2->first<C)
            it1++;
        else
            it2--;
    }
}

int main(int argc, char *argv[]) {
    ifstream in(argv[1]);
    ofstream of("output");

    // alternatively, could use the two step way:
    // ifstream in;
    // in.open(argv[1]);
    if (!in) {
        cout<<"Wrong file name!"<<endl;
        return 1;
    }
    
    int N;
    in>>N;
    
    string sbuf;
    for (int i=0; i<N; i++) {
        int C, I;
        in>>C;
        in>>I;

        getline(in, sbuf);
        getline(in, sbuf);
        stringstream ss(sbuf);
        vector<int> items;
        int temp;
        while (ss>>temp) 
            items.push_back(temp);
        of<<"Case #"<<i+1<<": ";
        findItems(items, C, I, of);
    }

    of.close();
    in.close();

    return 0;
}
