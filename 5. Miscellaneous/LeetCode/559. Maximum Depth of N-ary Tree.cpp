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
    int maxDepth(Node *root) {
        queue<Node *> q;
        if (root == NULL) {
            return 0;
        }
        int depth = 0;
        q.push(root);
        while (!q.empty()) {
            int n = q.size();
            depth++;
            while (n > 0) {
                Node *tmp = q.front();
                q.pop();
                for (int i = 0; i < tmp->children.size(); i++) {
                    q.push(tmp->children[i]);
                }
                n--;
            }
        }
        return depth;
    }
};