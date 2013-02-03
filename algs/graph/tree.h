#ifndef TREE_H
#define TREE_H

/***************************************************
 * Each node in the tree could have an arbitrary # *
 * of children. Using the leftchild, rightsibling  *
 * structure                                       *  
 ***************************************************/
#include <cstdio>
#include <cstdlib>

template<class CONTENT>
struct TreeNode {
  TreeNode *parent;
  TreeNode *first_child;
  TreeNode *right_sibling;
  CONTENT  content;

  TreeNode(CONTENT k):
    content(k),
    parent(NULL),
    first_child(NULL),
    right_sibling(NULL)
  {}
  ~TreeNode() {}
  TreeNode<CONTENT>* SearchSubTree(CONTENT);
  void PrintSubTree();
  void AddChild(TreeNode<CONTENT>*);
};

// Search the whole subtree rooted at this TreeNode
template<class CONTENT>
TreeNode<CONTENT>* TreeNode<CONTENT>::SearchSubTree(CONTENT key) {
  if(content == key) {
    printf("key = %d found!\n", key->key());
    return this;
  }

  TreeNode<CONTENT>* temp = first_child;
  TreeNode<CONTENT>* result = NULL;
  while(temp && result == NULL) {
    printf("searching subtree rooted at %d\n", temp->content->key());
    result = temp->SearchSubTree(key);
    temp = temp->right_sibling;
  }
  return result;
}

template<class CONTENT>
void TreeNode<CONTENT>::AddChild(TreeNode<CONTENT>* new_child) {
  if(first_child == NULL) {
    first_child = new_child;
  } else {
    TreeNode<CONTENT>* node_temp = first_child;
    while(node_temp->right_sibling) {
      node_temp = node_temp->right_sibling;
    }
    node_temp->right_sibling = new_child;
  }
  new_child->right_sibling = NULL;
  new_child->parent = this;
}

template<class CONTENT>
void TreeNode<CONTENT>::PrintSubTree() {
  if(content)
    printf("[node: %d] ->", content->key());
  else
    return;

  if(!first_child)
    printf("\n");
  TreeNode<CONTENT> *children = first_child;
  while(children) {
    children->PrintSubTree();
    printf("goto sibling of %d ", children->content->key());
    children = children->right_sibling;
    if(children)
      printf("= %d \n", children->content->key());
    else
      printf("= NULL \n");
  }

  return;
}

template<class CONTENT>
class Tree {
private:
  TreeNode<CONTENT> *root_;

public:
  Tree(): root_(NULL) {}
  ~Tree();
  TreeNode<CONTENT>* Search(CONTENT);
  void Insert(CONTENT, CONTENT);
  void Print();
};

template<class CONTENT>
void Tree<CONTENT>::Insert(CONTENT par, CONTENT chi) {
  if(!chi) {
    printf("child is NULL, return\n");
    return;
  }

  TreeNode<CONTENT> *chi_node = new TreeNode<CONTENT>(chi);
  if(!par) {
    root_ = chi_node;
  } else {
    TreeNode<CONTENT> *par_node = root_->SearchSubTree(par);
    if(par_node)
      par_node->AddChild(chi_node);
    else
      printf("par is not found\n");
  }
}

template<class CONTENT>
void Tree<CONTENT>::Print() {
  root_->PrintSubTree();
}

#endif // TREE_H
