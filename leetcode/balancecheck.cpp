#include <iostream>
#include <map>
#include <cmath>

using namespace std;

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
  map<TreeNode*, int> dpheight;
  
  int treeHeight(TreeNode *root) {
    if (!root)
      return 0;
    else if (dpheight.find(root) != dpheight.end()) {
      return dpheight[root];
    } else {
      int h = (1+max(treeHeight(root->left), treeHeight(root->right)));
      dpheight[root]=h;
      return h;
    }
  }
  
  bool isBalanced(TreeNode *root) {
    if (!root)
      return true;
    else {
      return (isBalanced(root->left) &
              isBalanced(root->right) &
              abs(treeHeight(root->left)-treeHeight(root->right))<=1
             );
    }
  }
};

int main() {
  Solution test;
  TreeNode *root = new TreeNode(1);
  TreeNode *lv2l = new TreeNode(2);
  TreeNode *lv2r = new TreeNode(3);
  root->left=lv2l;
  root->right=lv2r;

  TreeNode *lv3l = new TreeNode(4);
  TreeNode *lv3r = new TreeNode(5);
  TreeNode *lv3rr = new TreeNode(6);
  lv2l->left=lv3l;
  lv2l->right=lv3r;
  lv2r->right=lv3rr;
  TreeNode *lv4r = new TreeNode(7);
  lv3l->left=lv4r;


  cout << "result: "<< (test.isBalanced(root))<<endl;

  map<TreeNode*, int>::iterator mit=test.dpheight.begin();
  for(;mit!=test.dpheight.end(); mit++) {
    cout << mit->first<<": "<<mit->second<<endl;
  }

  return 0;
}

