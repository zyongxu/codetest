/*
 * Given a binary tree, check whether it is a mirror of itself (ie, symmetric around its center).
 *
 * For example, this binary tree is symmetric:
 *
 *     1
 *    / \
 *   2   2
 *  / \ / \
 * 3  4 4  3
 * But the following is not:
 *     1
 *    / \
 *   2   2
 *    \   \
 *     3   3
 * Note:
 * Bonus points if you could solve it both recursively and iteratively.
 *
 * iteratively: do a level order traversal, when a level is done, check
 * whether the values in the current buffer are symmetric or not
 */

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

bool levelCheck(deque<TreeNode*> lv) {
    if (lv.empty())
        return true;

    deque<TreeNode*>::iterator l = lv.begin();
    deque<TreeNode*>::iterator r = lv.end()-1;
    
    deque<TreeNode*> ret;
    
    while(l<r) {
        if(*l == NULL && *r==NULL) {
            l++;
            r--;
        } else if (*l==NULL || *r==NULL) {
            return false;
        } else {
            if((*l)->val != (*r)->val)
                return false;
            else {
                ret.push_front((*l)->right);
                ret.push_front((*l)->left);
                ret.push_back((*r)->left);
                ret.push_back((*r)->right);
            
                l++;
                r--;
            }
        }
    }
    return levelCheck(ret);
}

bool isSymmetric(TreeNode *root) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    if (!root)
        return true;
    deque<TreeNode*> test;
    test.push_back(root->left);
    test.push_back(root->right);
    
    return levelCheck(test);
}
