/* generate all unique tree structres with n nodes
 * recursion + DP
 */

#include <iostream>
#include <map>
#include <vector>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    map<int, vector<TreeNode *> > trees;
    
    Solution() {
        TreeNode *temp = NULL;
        trees[0] = vector<TreeNode*> (1, temp);
        trees[1] = vector<TreeNode*> (1, new TreeNode(1));
    }
    
    // increase the value in each node by n without changing
    // the structure of the tree
    TreeNode* copyIncrease(TreeNode *root, int n) {
        if (!root) 
            return NULL;
        TreeNode *newroot = new TreeNode(root->val+n);
        newroot->left =  copyIncrease(root->left, n);
        newroot->right = copyIncrease(root->right, n);
        return newroot;
    }
    
    vector<TreeNode *> generateTrees(int n) {
        if (trees.find(n) != trees.end()) {
            return trees[n];
        }
        
        // else
        vector<TreeNode *> ret;
        for (int i=0; i<n; i++) {
            vector<TreeNode *> lsub=generateTrees(i);
            vector<TreeNode *> rsub=generateTrees(n-1-i);
            
            int llen = lsub.size();
            int rlen = rsub.size();
            
            for (int m=0; m<llen; m++) {
                for (int n=0; n<rlen; n++) {
                    TreeNode *temp = new TreeNode(i+1);
                    temp->left = lsub[m];
                    temp->right = copyIncrease(rsub[n], i+1);
                    ret.push_back(temp);
                }
            }
        }
        trees[n] = ret;
        return ret;
    }
};

int main() {
    Solution test;
    vector<TreeNode*> ret = test.generateTrees(2);
    for (int i=0; i<ret.size(); i++) {
        cout<<ret[i]->val<<endl;
    }
    return 0;
}

