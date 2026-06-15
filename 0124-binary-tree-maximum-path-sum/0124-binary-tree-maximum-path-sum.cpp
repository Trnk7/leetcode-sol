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
    int sum=INT_MIN;
    int getSum(TreeNode* node){
        if(!node)return 0;

        int ls = max(0,getSum(node->left));
        int rs = max(0,getSum(node->right));

        sum = max(sum,ls+node->val+rs);

        return node->val+max(ls,rs);
    }
    int maxPathSum(TreeNode* root) {
        getSum(root);
        return sum;
    }
};