/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode *mergeKLists(vector<ListNode *> &lists) {
        ListNode* ret = new ListNode(0);
        ListNode* cur = ret;
        lists.erase(remove(lists.begin(), lists.end(), nullptr), lists.end());
        sort(lists.begin(), lists.end(), [] (ListNode* a, ListNode* b) {return a->val < b->val;});
        auto liter = lists.begin();
        
        while (lists.size() > 0) {
            cur->next = *liter;
            cur = *liter;
            *liter = (*liter)->next;
            if (!(*liter)) {
                lists.erase(liter);
            } else if (lists.size() > 1 && (*liter)->val >= (*(liter + 1))->val) {
                sort(lists.begin(), lists.end(), [] (ListNode* a, ListNode* b) {return a->val < b->val;});
            }
            liter = lists.begin();
        }   
        return ret->next;
    }
};
