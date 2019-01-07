/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Codec {
  public:
    // Encodes a tree to a single string.
    string serialize(TreeNode *root) {
        string res;
        serialize_helper(root, res);
        return res;
    }

    void serialize_helper(TreeNode *root, string &oss) {
        if (root == nullptr) {
            oss += "# ";
            return;
        }
        oss += to_string(root->val) + " ";
        serialize_helper(root->left, oss);
        serialize_helper(root->right, oss);
    }

    // Decodes your encoded data to tree.
    TreeNode *deserialize(string data) {
        istringstream iss(data);
        TreeNode *root = deserialize_helper(iss);
        return root;
    }

    TreeNode *deserialize_helper(istringstream &iss) {
        string current_input;
        iss >> current_input;
        if (current_input == "#")
            return nullptr;
        else {
            TreeNode *result = new TreeNode(stoi(current_input));
            result->left = deserialize_helper(iss);
            result->right = deserialize_helper(iss);
            return result;
        }
    }
};

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.deserialize(codec.serialize(root));