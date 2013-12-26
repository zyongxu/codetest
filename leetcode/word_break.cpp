#include <unordered_set>
#include <unordered_map>
#include <iostream>
#include <vector>
using namespace std;

struct Node {
    Node(char c):
        letter(c),
        end_of_word(false)
    {}

    char letter;
    bool end_of_word;
    unordered_map<char, Node*> children;
};

class Solution {
public:
    Solution():
        root('\0')
    {}

    bool wordBreak(string s, unordered_set<string> &dict) {
        buildWordTree(dict);
        int len = s.size();
        vector<bool> bp(len + 1, false);
        bp[len] = true;
        for (int i=len-1; i>=0; i--) {
            cout << i << endl;
            for (int j=i; j<len; j++) {
                bool rc = check(s.substr(i, j-i+1)) & bp[j+1];
                cout << j << ": " << s.substr(i, j-i+1) << endl;
                if (rc) {
                    bp[i] = true;
                    break;
                }
            }
        }

        return bp[0];
    }

    void buildWordTree(unordered_set<string> &dict) {
        for (auto& word : dict) {
            int len = word.size();
            Node *cur = &root;
            for (int i=0; i<len; i++) {
                if (cur->children.count(word[i]) == 0) {
                    cur->children.insert(make_pair(word[i], new Node(word[i])));
                }
                cur = cur->children.at(word[i]);
            }
            cur->end_of_word = true;
        }
    }

    bool check(const string& word) {
        int len = word.size();
        Node *cur = &root;
        for (int i=0; i<len; i++) {
            if (cur->children.count(word[i]) > 0)
                cur = cur->children.at(word[i]);
            else
                return false;
        }
        return cur->end_of_word;
    }

private:
    Node root;
};

int main() {
    Solution s;
    unordered_set<string> ws = {"dog", "s", "gs"};
    cout << (s.wordBreak("dogs", ws)) << endl;
    return 0;
}
