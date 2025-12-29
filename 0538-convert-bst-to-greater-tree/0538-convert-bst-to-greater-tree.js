/**
 * Definition for a binary tree node.
 * function TreeNode(val, left, right) {
 *     this.val = (val===undefined ? 0 : val)
 *     this.left = (left===undefined ? null : left)
 *     this.right = (right===undefined ? null : right)
 * }
 */
/**
 * @param {TreeNode} root
 * @return {TreeNode}
 */
var convertBST = function(root) {
    var sum=0;
    var trv = function(root){
        if(root==null)return;
        trv(root.right);
        sum+=root.val;
        root.val=sum;
        trv(root.left);
    }
    trv(root);
    return root;
};