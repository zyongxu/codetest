#include <cstdio>
#include <cstdlib>

class Node {
private:
  Node *next_;
  int key_;
  char *data_;

public:
  Node(int key): key_(key), data_(NULL) {}
  ~Node() {
    if(data_)
      delete data_;
    return;
  }

  Node* next() {return next_;}
  void SetNext(Node *nnode) { next_=nnode; }
  int key() {return key_;}
  void SetKey(int ky) { key_=ky; }
  char* data() {return data_;}
};

class LinkedList {
private:
  Node* head_;

public:
  LinkedList();
  ~LinkedList();
  Node* Search(int);
  void Insert(Node*);
  void Delete(int);
  void PrintList();
};

LinkedList::LinkedList() {
  head_ = NULL;
}

LinkedList::~LinkedList() {
  Node* cur = head_;
  Node* next = NULL;
  while(cur) {
    next = cur->next();
    delete cur;
    cur = next;
  }
}

Node* LinkedList::Search(int key) {
  Node *temp = head_;
  while(temp && temp->key() != key)
    temp = temp->next();
  return temp;
}

void LinkedList::Insert(Node *new_node) {
  if(!head_) {
    head_ = new_node;
    return;
  }

  Node *temp = head_;
  while(temp->next())
    temp = temp->next();
  temp->SetNext(new_node);
  new_node->SetNext(NULL);
}

void LinkedList::Delete(int key) {
  Node *pre = NULL;
  Node *cur = head_;
  if(cur->key() == key) {
    head_ = cur->next();
    delete cur;
    return;
  }

  while(cur && cur->key() != key) {
    pre = cur;
    cur = cur->next();
  }
  
  if(!cur)
    return;
  else {
    pre->SetNext(cur->next());
    delete cur;
  }
}

void LinkedList::PrintList() {
  Node *temp = head_;
  while (temp) {
    printf("%d\n", temp->key());
    temp = temp->next();
  }
}

int main() {
  LinkedList *ll1 = new LinkedList();
  for(int i = 0; i<10; i++) {
    Node *anode = new Node(i*3-1);
    ll1->Insert(anode);
  }
  ll1->PrintList();
  delete ll1;
  return 0;
}
