#include <iostream>
#include <vector>
#include <deque>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

vector<vector<int> > levelOrder(TreeNode *root) {
    if (!root)
        return vector<vector<int> >();
        
    int cur_lv=1;
    int next_lv=0;
    deque<TreeNode*> nqueue;
    nqueue.push_back(root);
    
    vector<vector<int> > ret;
    TreeNode *temp = NULL;
    vector<int> vbuf;
    while (!nqueue.empty()) {
        temp = nqueue.front();
        nqueue.pop_front();
        cur_lv--;
        vbuf.push_back(temp->val);
        
        if (temp->left) {
            nqueue.push_back(temp->left);
            next_lv++;
        }
        if (temp->right) {
            nqueue.push_back(temp->right);
            next_lv++;
        }
        if (cur_lv==0) {
            ret.push_back(vbuf);
            vbuf.clear();
            cur_lv = next_lv;
            next_lv = 0;
        }
    }
    return ret;
}


int main() {
    TreeNode *n1 = new TreeNode(1);
    TreeNode *n2 = new TreeNode(2);
    TreeNode *n3 = new TreeNode(3);
    TreeNode *n4 = new TreeNode(4);
    TreeNode *n5 = new TreeNode(5);
    n1->left = n2;
    n1->right = n3;
    n2->left = n4;
    n3->right = n5;

    levelOrder(n1);
    return 0;
}
