/*
 * Given a binary tree, find the maximum path sum.
 *
 * The path may start and end at any node in the tree.
 *
 * For example:
 * Given the below binary tree,
 *
 *        1
 *       / \
 *      2   3
 * 
 * Return 6.
 */
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
private:
    int maxsum;
public:
    int maxPath(TreeNode *root) {
        if (!root)
            return 0;
        
        int l=maxPath(root->left);
        int r=maxPath(root->right);
        
        maxsum = maxsum > root->val+l+r ? maxsum : root->val+l+r;
        
        return max(root->val+max(l,r), 0);
    }
    
    int maxPathSum(TreeNode *root) {
        maxsum = -9999;
        maxPath(root);
        
        return maxsum;
    }
};
