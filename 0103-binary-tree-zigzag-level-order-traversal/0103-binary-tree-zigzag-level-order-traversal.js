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
 * @return {number[][]}
 */
var zigzagLevelOrder = function(root) {
    if (!root) return [];
    let queue = [root];
    let res = [];
    let flag=1
    while (queue.length) {
        let len = queue.length;
        let temp = [];
        for (let i = 0; i < len; i++) {
            let node = queue.shift();
            temp.push(node.val);
            if (node.left) queue.push(node.left);
            if (node.right) queue.push(node.right);
        }
        if(res.length%2!=0){
            temp = temp.reverse()
        }
        res.push(temp);
    }
    return res;
};