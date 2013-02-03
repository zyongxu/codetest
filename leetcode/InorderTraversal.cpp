/*
 * iterately in-order traverse a binary tree
 */
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    vector<int> inorderTraversal(TreeNode *root) {
        //always forget check the input!!!
        if (!root)
            return vector<int>();
            
        vector<int> ret;
        stack<TreeNode*> nstack;
        TreeNode *cur=root;
        while(true) {
            if(cur) {
                // keep going left
                nstack.push(cur);
                cur = cur->left;
            } else {
                if (nstack.empty())
                    break;
                // if no "left" to go, print the top of stack (the parent of the NULL left)
                cur = nstack.top();
                nstack.pop();
                ret.push_back(cur->val);
                // then go right
                cur=cur->right;
            }
        }
        return ret;
    }
};
