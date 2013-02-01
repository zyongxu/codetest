#ifndef FILEFIXIT_H
#define FILEFIXIT_H
#include "base.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

struct TreeNode {
    string dir;
    vector<TreeNode*> children;
    
    TreeNode(string n): dir(n) { children.clear(); }

    TreeNode* findChild(string dir) {
        int len = children.size();
        for (int i=0; i<len; i++) {
            if (children[i]->dir == dir)
                return children[i];
        }
        return NULL;
    }

    TreeNode *insertChild(string dir) {
        TreeNode *newchild  = new TreeNode (dir);
        children.push_back(newchild);
        return newchild;
    }

    //path should begin with the first dir instead of the root dir '/'
    void insertPath(string path) {
        if (path.size()<1)
            return;

        size_t pos = path.find_first_of('/');
        string curdir = path.substr(0, pos);
        TreeNode *next = findChild(curdir);
        if (!next)
            next = insertChild(curdir);
        // has to explicitly check pos != npos here!!
        // Otherwise, npos may be used as the start position
        // of the substr, cause an exception to be thrown
        if (pos != string::npos)
            next->insertPath(path.substr(pos+1));
    }

    void mkdir(string path, int &cnt) {
        if (path.empty())
            return;
        size_t pos = path.find_first_of('/');
        string curdir = path.substr(0, pos);
        TreeNode *next = findChild(curdir);
        if (!next) {
            cnt++;
            next = insertChild(curdir);
        }
        if (pos != string::npos)
            next->mkdir(path.substr(pos+1), cnt);
    }
};

class Solution : public BaseSolu{
public:
    TreeNode *root;
    int M;
public:
    void casePrepare(ifstream &in) {
        int N;
        in>>N>>M;
        root = new TreeNode("\0");
        for (int i=0; i<N; i++) {
            string buf;
            in>>buf;
            root->insertPath(buf.substr(1));
        }
    }

    int run(ifstream &in) {
        string buf;
        int cnt=0;
        for (int i=0; i<M; i++) {
            in>>buf;
            root->mkdir(buf.substr(1), cnt);
        }
        return cnt;
    }
};

#endif
