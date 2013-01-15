#include <iostream>
#include <stack>
#include <vector>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

vector<int> inorderTraversal(TreeNode *root) {
  if (!root)
    return vector<int>();
      
  vector<int> ret;
  stack<TreeNode*> nstack;
  TreeNode *temp = root;
  
  while (temp->left) {
    nstack.push(temp);
    temp = temp->left;
  }

  while (!nstack.empty()) {
    if (!temp->left) {
        ret.push_back(temp->val);
        if (temp->right) {
          temp = temp->right;
        } else {
          temp = nstack.top();
          ret.push_back(temp->val);
          nstack.pop();
        }
    } else {
      nstack.push(temp);
      temp = temp->left;
    }
  }
  return ret;
}


int main() {
  TreeNode *root = new TreeNode(5);
  inorderTraversal(root);
  
  return 0;
}
