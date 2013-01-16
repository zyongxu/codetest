/*
 * Populate each next pointer to point to its next right node. 
 * If there is no next right node, the next pointer should be set to NULL.
 *
 * Initially, all next pointers are set to NULL.
 *
 * Note:
 *
 * You may only use constant extra space.
 * You may assume that it is a perfect binary tree 
 * (ie, all leaves are at the same level, and every parent has two children).
 * For example,
 * Given the following perfect binary tree,
 *          1
 *         /  \
 *        2    3
 *       / \  / \
 *      4  5  6  7
 * After calling your function, the tree should look like:
 *          1 -> NULL
 *         /  \
 *        2 -> 3 -> NULL
 *       / \  / \
 *      4->5->6->7 -> NULL
 *
 * Strategy: Every node's next was set by its parent, every node set it's TWO children's 
 *           next. (Not only cur->left->next = cur->right, but also 
 *                  cur->right->next = cur->next->left)
 */

struct TreeLinkNode {
 int val;
 TreeLinkNode *left, *right, *next;
 TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
};

class Solution {
public:
    void connect(TreeLinkNode *root) {
        if (!root)
            return;
        
        if (!root->next) {
            if (root->left) {
                root->left->next = root->right;
                connect(root->left);
                connect(root->right);
            } else {
                return;
            }
        } else {
            if (root->left) {
                root->left->next = root->right;
                root->right->next = root->next->left;
                connect(root->left);
                connect(root->right);
            } else {
                return;
            }
        }
    }
};
