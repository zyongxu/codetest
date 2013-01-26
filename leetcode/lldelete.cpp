/*
 * Given a sorted linked list, delete all nodes that have duplicate numbers, leaving only distinct numbers from the original list.
 * 
 * For example,
 * Given 1->2->3->3->4->4->5, return 1->2->5.
 * Given 1->1->1->2->3, return 2->3.
 *
 * Sol: Look back and ahead to check duplicate!
 *      Use a guard at the begining since the head may change
 */

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode *deleteDuplicates(ListNode *head) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if (!head)
            return NULL;
            
        ListNode *g = new ListNode(head->val-1);
        ListNode *dFrom = g;
        ListNode *pre = g;
        ListNode *cur=head;
        
        while (cur) {
            if (pre->val != cur->val && (!cur->next || cur->next->val != cur->val)) {
                dFrom->next = cur;
                dFrom = cur;
            }
            pre=cur;
            cur=cur->next;
            
        }
        dFrom->next = cur;
        return g->next;
    }
};
