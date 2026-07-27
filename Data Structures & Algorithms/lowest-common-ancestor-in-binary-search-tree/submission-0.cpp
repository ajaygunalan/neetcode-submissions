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
    TreeNode* lowestCommonAncestor(TreeNode* node, TreeNode* p, TreeNode* q) {
        if(!node)
            return nullptr;

        TreeNode* nodeRes;

        if(node->val < p->val && node->val < q->val)
            nodeRes = lowestCommonAncestor(node->right, p, q);

        else if(node->val > p->val && node->val > q->val)
            nodeRes = lowestCommonAncestor(node->left, p, q);

        else
            return node;

        return nodeRes;
    }
};
