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
    int rangeSumBST(TreeNode *root, int L, int R) {
        if (root == nullptr) {
            return 0;
        }
        int sum_value = root->val;
        if (sum_value > R || sum_value < L)
            sum_value = 0;
        sum_value +=
            rangeSumBST(root->left, L, R) + rangeSumBST(root->right, L, R);
        return sum_value;
    }
};