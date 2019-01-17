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
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> result;
        stack<TreeNode*> node_stack;
        if(root==nullptr){
            return result;
        }
        TreeNode* cur = root;
        do{
            
            while(cur!=nullptr){
                node_stack.push(cur);
                cur = cur->left;
            }
            cur = node_stack.top();
            result.push_back(cur->val);
            node_stack.pop();
            cur = cur->right;
        }while(!node_stack.empty() || cur!=nullptr);
        return result;     
    }
    
};
