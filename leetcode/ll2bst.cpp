/*
 * Given a singly linked list where elements are sorted in ascending order, 
 * convert it to a height balanced BST.
 */
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    TreeNode *sortedListToBST(ListNode *head) {
        if(!head)
            return NULL;
        else if (!head->next)
            return (new TreeNode(head->val));

        ListNode *fast = head;
        ListNode *slow = head;
        ListNode *prevslow = NULL;
        // The way to handl faster and slower pointers
        // on a linked list! check the fast's first hop 
        // before hop the slower!
        while(fast) {
            fast=fast->next;
            if (!fast)
                break;
            else {
                prevslow = slow;
                slow=slow->next;
                fast=fast->next;
            }
        }
        
        TreeNode *root = new TreeNode(slow->val);
        fast = slow->next;
        prevslow->next = NULL;

        root->left = sortedListToBST(head);
        root->right = sortedListToBST(fast);
        return root;
    }
};
