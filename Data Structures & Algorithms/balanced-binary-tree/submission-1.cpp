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
    bool isBalanced(TreeNode* root) {
        TreeNode* node = root;
        return heightCalculator(node) != -1;
    }

    int heightCalculator(TreeNode* node) {
        if(!node)
            return 0;

        int left_height = heightCalculator(node->left);
        if (left_height == -1)
            return -1;

        int right_height = heightCalculator(node->right);
        if (right_height == -1) 
            return -1;

        if (abs(right_height - left_height) > 1)
            return -1;
            
        return 1 + max(left_height, right_height);
    }

private:
};