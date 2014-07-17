#include <iostream>

struct ListNode {
   int val;
   ListNode *next;
   ListNode(int x) : val(x), next(NULL) {}
};

    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
        int carrier = 0;
        ListNode *ret = new ListNode(-1);
        ListNode *cur = ret;
        while (l1 || l2) {
            int l1val = 0, l2val=0;
            if (l1) {
                l1val = l1->val;
                l1 = l1->next;
            }
            if (l2) {
                l2val = l2->val;
                l2 = l2->next;
            }
            
            int plus = l1val + l2val + carrier;
            ListNode *nret = new ListNode(plus%10);
            cur->next = nret;
            cur = nret;
            carrier = plus % 10;
        }
        return ret->next;
    }

int main() {
  ListNode *i1 = new ListNode(1);
  ListNode *i2 = new ListNode(1);

  addTwoNumbers(i1, i2);
  
  return 0;
}  
