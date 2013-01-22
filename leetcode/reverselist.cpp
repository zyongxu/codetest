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
    ListNode *guard = new ListNode (-1);
    guard->next = head;
    ListNode *pp = guard;
    ListNode *p = head;
    ListNode *cur = head->next;
    int cnt = 1;
    
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

