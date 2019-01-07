/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};
*/
class Solution {
  public:
    vector<int> preorder(Node *root) {
        vector<int> ret;
        dfs(root, ret);
        return ret;
    }

    void dfs(Node *root, vector<int> &ret) {
        if (root == nullptr) {
            return;
        }
        ret.push_back(root->val);
        for (auto x : root->children) {
            dfs(x, ret);
        }
    }
};