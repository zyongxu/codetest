/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    bool checksubtree(TreeNode *root, int l, int r) {
        if (!root)
            return true;
            
        if (l>=root->val || r<=root->val)
            return false;
        else {
            return (checksubtree(root->left, l, root->val) &
                    checksubtree(root->right, root->val, r));
        }
    }
    bool isValidBST(TreeNode *root) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        return checksubtree(root, INT_MIN, INT_MAX);
    }
};
