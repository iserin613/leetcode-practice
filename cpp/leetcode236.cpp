/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
 class Solution {
    public:
        TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
            return dfs(root,p,q);
            
            
        }
    private:
    TreeNode* dfs(TreeNode* root,TreeNode* p,TreeNode* q){
        if(root==nullptr)return nullptr;
        if(root==p||root==q)return root;
        TreeNode* left=dfs(root->left,p,q);
        TreeNode* right=dfs(root->right,p,q);
        if(left!=nullptr&&right!=nullptr)return root;
        if(left!=nullptr)return left;
        return right;
    }

        
    };