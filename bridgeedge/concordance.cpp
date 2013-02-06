/*
 * Problem: DHM Concordance V2
 * Candidate: Yongxu Zhang
 *
 * Tested in 
 *   OS:       Mac OS X 10.8.2
 *   Compiler: i686-apple-darwin11-llvm-g++-4.2
 *
 * [Usage]
 *   1. Compile:  g++ concordance.cpp
 *   2. Run:      ./a.out test_file.txt
 *   3. The result will be displayed through stdout
 * 
 * [Note]
 *   This problem might be easier to solve in a scripting language. 
 *   However, in order to present my skill in the programming language 
 *   that I might use most in this position, I chose C++.
 *   
 *   I tested the program with the example in the description of the problem
 *   and it worked well.
 *
 *   I handled non-alphabetic characters as following:
 *    1. Every character inside a word is kept
 *    2. Non-alphabetic characters, expect the '.', at the end of a WORD are removed
 *    3. '.' '?' '!' at the end of a SENTENCE are removed
 */

#include <iostream>
#include <fstream>
#include <map>
#include <stack>
#include <vector>
#include <cstdio>
#include <iomanip>
using namespace std;

void wordCount (ifstream &fin) {
    // a stack to store all the words in the current sentence
    stack<string> cur_sent;
    // a map to store the final word counts and line numbers
    map<string, vector<int> > word_list;
    string word;
    int line_num=1;
    fin>>word;
    cur_sent.push(word);

    // STEP 1: build the word count list
    while(fin.good()) {
        // come to the EOF or a capitalized word 
        if (!(fin>>word) || isupper(word[0])) {
            string temp = cur_sent.top();
            // if the last word ends with a period
            if (temp[temp.size()-1]=='.' 
                    || temp[temp.size()-1]=='?'
                    || temp[temp.size()-1]=='!') {

                temp.erase(temp.size()-1);
                cur_sent.top() = temp;
                //pop all the elements from the cur_sent
                //and update the word_list
                while (!cur_sent.empty()) {
                    temp = cur_sent.top();
                    cur_sent.pop();
                    temp[0]=tolower(temp[0]);
                    int tail = temp.size()-1;
                    if (!isalpha(temp[tail]) && temp[tail] != '.')
                        temp.erase(tail);
                    if (word_list[temp].empty())
                        word_list[temp].push_back(1);
                    else 
                        word_list[temp][0]++;
                    word_list[temp].push_back(line_num);
                }
                line_num++;
            }
        }
        cur_sent.push(word);
    }

    // STEP 2: display the word count list
    map<string, vector<int> >::iterator mit;
    for (mit=word_list.begin(); mit != word_list.end(); mit++) {
        cout<<setw(16)<<left<<mit->first<<"{"<<mit->second[0]<<":"
            <<mit->second[1];
        int vlen = mit->second.size();
        for (int i=2; i<vlen; i++) 
            cout<<","<<mit->second[i];
        cout<<"}"<<endl;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cout<<"Usage: "<<argv[0]<<" <file_name>"<<endl;
        return 0;
    }

    ifstream fin(argv[1]);
    if (!fin) {
        cout<<"Could not open \"<<filename<<\""<<endl;
        return 0;
    }

    wordCount(fin);
    return 0;
}

