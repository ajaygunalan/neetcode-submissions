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
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        // An empty window means no nodes live here.
        if(preorder.empty())
            return nullptr;

        int rootValue = preorder[0];
        int rootIndex = 0;
        for(int i=0; i<inorder.size(); i++){
            if(inorder[i] == rootValue)
                rootIndex = i;
        }

        // Everything before rootIndex in order belong to the left subtree
        // so the size of left subtree is =:
        int leftSzie = rootIndex;

        TreeNode* root = new TreeNode(rootValue);


        //inorder(left, node, right)
        //preorder(node, left, right)

        //Left subtree cut into preorder and inorder
        vector<int> leftPreorder(preorder.begin( )+1, preorder.begin()+1+leftSzie );
        vector<int> leftInorder(inorder.begin(), inorder.begin()+leftSzie);

        //Right subtree cut into preorder and postorder
        vector<int> rightPreorder(preorder.begin()+1+leftSzie, preorder.end());
        vector<int> rightInorder(inorder.begin() + 1 + leftSzie, inorder.end());

        //recurive call on them 
        root->left =  buildTree(leftPreorder, leftInorder);
        root->right = buildTree(rightPreorder, rightInorder);
        return root;
    }
};
