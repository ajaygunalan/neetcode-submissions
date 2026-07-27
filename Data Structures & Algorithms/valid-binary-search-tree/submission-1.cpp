class Solution {
public:
    bool isValidBST(TreeNode* node, long minVal = LONG_MIN, long maxVal = LONG_MAX) {
        if(!node)
            return true;

        if(node->val <= minVal || node->val >= maxVal)
            return false;
        
        return isValidBST(node->left, minVal, node->val) && isValidBST(node->right, node->val, maxVal);
    }
};