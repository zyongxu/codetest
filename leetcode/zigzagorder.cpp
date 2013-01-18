struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    vector<vector<int> > zigzagLevelOrder(TreeNode *root) {
        if(!root)
            return vector<vector<int> >();
        
        deque<TreeNode*> buffer;
        vector<vector<int> > ret;
        vector<int> lvbuffer;
        int cur_lv=1;
        int next_lv=0;
        
        buffer.push_back(root);
        TreeNode *temp;
        while(!buffer.empty()) {
            temp = buffer.front();
            buffer.pop_front();
            cur_lv--;
            lvbuffer.push_back(temp->val);
            if (temp->left) {
                buffer.push_back(temp->left);
                next_lv++;
            }
            if (temp->right) {
                buffer.push_back(temp->right);
                next_lv++;
            }
            
            if(cur_lv==0) {
                if(ret.size()%2==1) {
                    reverse(lvbuffer.begin(), lvbuffer.end());
                }
                ret.push_back(lvbuffer);
                lvbuffer.clear();
                cur_lv = next_lv;
                next_lv = 0;
            }
            
        }
        return ret;
    }
};

