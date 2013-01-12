#include <iostream>

struct ListNode {
   int val;
   ListNode *next;
   ListNode(int x) : val(x), next(NULL) {}
};

ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
    ListNode *ret = NULL;
    ListNode *pre = NULL;
    int carry = 0;

    if (l1 && l2) {
        ret = new ListNode( (l1->val + l2->val) % 10 );
        carry = (l1->val + l2->val)/10;
        l1 = l1->next;
        l2 = l2->next;
        pre = ret;
    }
    
    while(l1 && l2) {
        ListNode *temp = new ListNode( (l1->val + l2->val + carry) % 10 );
        carry = (l1->val+l2->val+carry)/10;
        pre->next = temp;
        pre = temp;
        l1 = l1->next;
        l2 = l2->next;
    }
    
    ListNode *left = NULL;
    if (l1)
        left = l1;
    else if (l2)
        left = l2;
    
    while (left) {
        ListNode *temp = new ListNode( (left->val + carry)%10 );
        carry = (left->val+carry)/10;
        pre->next = temp;
        pre = temp;
        left = left->next;
    }
    
    if (carry) {
        ListNode *temp = new ListNode(carry);
        pre->next = temp;
    }
    
    return ret;
}


int main() {
  ListNode *i1 = new ListNode(1);
  ListNode *i2 = new ListNode(1);

  addTwoNumbers(i1, i2);
  
  return 0;
}  
