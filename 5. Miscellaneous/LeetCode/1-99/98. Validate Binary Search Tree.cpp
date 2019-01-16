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
    bool isValidBST(TreeNode* root) {
        int x, y;
        return isValidBSTHelper(root, x, y);
    }
    
    bool isValidBSTHelper(TreeNode* root, int& minval, int& maxval){
        if(root == nullptr){
            minval = numeric_limits<int>::max();
            maxval = numeric_limits<int>::min();
            return true;
        }
        else{
            int minval_l, minval_r, maxval_l, maxval_r;
            bool valid_l = isValidBSTHelper(root->left, minval_l, maxval_l);
            if(!valid_l)
                return false;
            bool valid_r = isValidBSTHelper(root->right, minval_r, maxval_r);
            if(!valid_r)
                return false;
            if(root->val <= maxval_l && root->left!=nullptr || root->val >= minval_r && root->right!=nullptr){
                return false;
            }
            minval = min(root->val, minval_l);
            maxval = max(root->val, maxval_r);
            return true;
        }
    }
};


class Solution2 {
public:
    bool isValidBST(TreeNode* root) {
        return isValidBST(root, NULL, NULL);
    }

    bool isValidBST(TreeNode* root, TreeNode* minNode, TreeNode* maxNode) {
        if(!root) return true;
        if(minNode && root->val <= minNode->val || 
           maxNode && root->val >= maxNode->val)
            return false;
        return isValidBST(root->left, minNode, root) && 
            isValidBST(root->right, root, maxNode);
    }
};
