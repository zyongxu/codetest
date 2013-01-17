/*
 * When using recursion, USE the return of the recursive call
 * as if it is the desired and correct result without worrying
 * about how to ensure its correctness. Only focus on the current
 * recursion!!!!!!!
 *
 * The binary tree flattened by this way is not recoverable!
 */
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:

    TreeNode *flattenSubtree(TreeNode *root) {
        if (!root)
            return NULL;
        else if (!root->left && !root->right)
            return root;
    
        TreeNode *l = root->left;
        TreeNode *r = root->right;
        TreeNode *ltail = flattenSubtree(l);
        TreeNode *rtail = flattenSubtree(r);
        root->left=NULL;
        root->right = l;
        if (ltail && r) {
            ltail->right = r;
            return rtail;
        } else if (!ltail && r) {
            root->right = r;
            return rtail;
        } else if (ltail && !r) {
            return ltail;
        } else
            return root;
    }

    void flatten(TreeNode *root) {
        if (!root)
            return;
        
        flattenSubtree(root);
        
    }
};
