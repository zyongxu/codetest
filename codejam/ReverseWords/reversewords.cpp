#include <iostream>
#include <fstream>
#include <sstream>
#include <stack>
using namespace std;

int main(int argc, char *argv[]) {
    ifstream in(argv[1]);
    if (!in) {
        cout<<"wrong file name!"<<endl;
        return 1;
    }
    ofstream out("output");

    int N;
    in>>N;
    string sbuf;
    getline(in, sbuf);

    for (int i=0; i<N; i++) {
        getline(in, sbuf);
        stack<string> s;
        string word;
        istringstream oss(sbuf);
        while (oss>>word)
            s.push(word);
        string ret = s.top();
        s.pop();
        while(!s.empty()) {
            ret += " ";
            ret += s.top();
            s.pop();
        }
        out<<"Case #"<<i+1<<": "<<ret<<endl;
    }

    in.close();
    out.close();
    return 0;
}
