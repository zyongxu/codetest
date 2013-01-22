#include <iostream>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

ListNode *reverseBetween(ListNode *head, int m, int n) {
    if(!head)
        return head;
    // add a guard before the head since head may change if the first node
    // is reversed. guard->next is always the correct head!
    ListNode *guard = new ListNode (-1);
    guard->next = head;
    // the previous-previous node of the current node. pp->next is the last node
    // which is not reversed! So change pp->next->next to point to the new reversed
    // list!
    ListNode *pp = guard;
    ListNode *p = head;
    ListNode *cur = head->next;
    int cnt = 1;
    
    // check cur != NULL is not always working! In this case, if cur=NULL but cnt = n
    // we still want to go through one more iteration!
    while (true) {
        if (cnt<m) {
            pp=p;
            p=cur;
            cur = cur->next;
        } else if (cnt>=m && cnt<n) {
            ListNode *nex = cur->next;
            cur->next = p;
            p = cur;
            cur = nex;
        } else if (cnt == n) {
            pp->next->next = cur;
            pp->next = p;
            break;
        }
        
        cnt++;
    }
    return guard->next;
}

int main() {
    ListNode *n1 = new ListNode(-1);
    ListNode *n2 = new ListNode(-3);
    n1->next = n2;

    ListNode *ret = reverseBetween(n1, 1, 2);
        cout<<ret->val<<endl;
        ret = ret->next;
        cout<<ret->val<<endl;
    return 0;
}

