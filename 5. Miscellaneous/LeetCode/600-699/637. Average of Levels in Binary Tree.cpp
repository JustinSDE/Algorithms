/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
  public:
    vector<double> averageOfLevels(TreeNode *root) {
        queue<TreeNode *> lvl;
        if (root == nullptr)
            return vector<double>{};
        lvl.push(root);
        vector<double> ret;
        while (!lvl.empty()) {
            long long sum = 0;
            int cnt = 0;
            int sz = lvl.size();
            for (int i = 0; i < sz; i++) {
                TreeNode *temp = lvl.front();
                lvl.pop();
                sum += temp->val;
                cnt++;
                if (temp->left)
                    lvl.push(temp->left);
                if (temp->right)
                    lvl.push(temp->right);
            }
            ret.push_back(double(sum) / cnt);
        }
        return ret;
    }
};