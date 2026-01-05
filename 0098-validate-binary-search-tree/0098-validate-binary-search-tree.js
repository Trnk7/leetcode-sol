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
 * @return {boolean}
 */

 const checkNode = (root, minVal, maxVal) => {
    if(!root) return true
    if(root.left === null && root.right === null) {
        if(root.val < maxVal && root.val > minVal) return true
        return false
    }
    if(root.val <= minVal || root.val >=maxVal) return false
    return checkNode(root.left, minVal, root.val) && checkNode(root.right, root.val, maxVal)
}

var isValidBST = function(root) {
    return checkNode(root, -Infinity,Infinity)
};