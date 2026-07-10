/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */

class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
    TreeNode* node = root;
    if (!node)
        return node;

    TreeNode* left  = node->left;
    TreeNode* right = node->right; 

    invertTree(node->left);
    invertTree(node->right);
    
    node->left = right;
    node->right = left;

    return root;
    }
};
