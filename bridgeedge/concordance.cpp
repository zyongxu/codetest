/* Keeps the word as-it-is, only remove the tailing dot if it is
 * a period. Other special characters such as hyphen, underscore will
 * be kept in the word
 */

#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <cstdio>
#include <iomanip>
using namespace std;

void wordCount(ifstream &fin) {
    string cur_word;
    string next_word;
    map<string, vector<int> > concordance;
    int line_nu = 1;
    bool incre_ln = false;
    
    fin>>cur_word;
    while (fin>>next_word) {
        int wlen = cur_word.size();
        if (cur_word[wlen-1] == '.') {
            if (isupper(next_word[0])) {
                incre_ln = true;
                cur_word.erase(wlen-1);
            }
        } else if (!isalpha(cur_word[wlen-1]))
            cur_word.erase(wlen-1);

        cur_word[0]=tolower(cur_word[0]);
        if (concordance[cur_word].empty())
            concordance[cur_word].push_back(0);

        concordance[cur_word][0]++;
        concordance[cur_word].push_back(line_nu);
        if (incre_ln) {
            incre_ln = false;
            line_nu++;
        }
        cur_word = next_word;
    }

    int wlen = cur_word.size();
    if (cur_word[wlen-1] == '.')
        cur_word.erase(wlen-1);

    cur_word[0]=tolower(cur_word[0]);
    if (concordance[cur_word].empty())
        concordance[cur_word].push_back(0);

    concordance[cur_word][0]++;
    concordance[cur_word].push_back(line_nu);

    map<string, vector<int> >::iterator mit;
    for (mit=concordance.begin(); mit != concordance.end(); mit++) {
        cout<<setw(16)<<left<<mit->first<<"{"<<mit->second[0]<<":"
            <<mit->second[1];
        int vlen = mit->second.size();
        for (int i=2; i<vlen; i++) 
            cout<<","<<mit->second[i];
        cout<<"}"<<endl;
    }
}

int main() {
    string filename;
    cout<<"Please enter the file name to be processed>> ";
    cin>>filename;

    ifstream fin(filename.c_str());
    if (!fin) {
        cout<<"Could not open \"<<filename<<\""<<endl;
        return 0;
    }

    wordCount(fin);
    return 0;
}
