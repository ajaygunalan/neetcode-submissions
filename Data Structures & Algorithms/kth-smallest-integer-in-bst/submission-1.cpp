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
    int kthSmallest(TreeNode* node, int k) {

        // traverse the tree in-order(left, node, right)
        // once you recah the left most start counter at k=1
        // if(counter == k)  return node->val; 
        int counter = 0;
        int result = 0;
        inOrderTraverse(node, k, counter, result);
        return result;
    }


    void inOrderTraverse(TreeNode* node, int k, int& counter, int& result){

        if(!node) return;

        inOrderTraverse(node->left, k, counter, result);
    
        counter++;
        if(counter == k) {
            result = node->val;
            return;

        }
 
        inOrderTraverse(node->right, k, counter, result);
    }


};
