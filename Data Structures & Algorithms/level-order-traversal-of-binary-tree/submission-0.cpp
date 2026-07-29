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
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> result;
        queue<TreeNode*> nodesToVisit;

        if(!root)
            return result;
        

        nodesToVisit.push(root);
        while(!nodesToVisit.empty()) {
            int nodesInCurrentLevel = nodesToVisit.size();
            vector<int> levelAns;

            for(int i=0; i< nodesInCurrentLevel; i++) {
                TreeNode* currentNode = nodesToVisit.front();
                nodesToVisit.pop();

                levelAns.push_back(currentNode->val);

                if(currentNode->left)
                    nodesToVisit.push(currentNode->left);
                if(currentNode->right)
                    nodesToVisit.push(currentNode->right);
            }
            result.push_back(levelAns);
        }
        return result;
    }
};
