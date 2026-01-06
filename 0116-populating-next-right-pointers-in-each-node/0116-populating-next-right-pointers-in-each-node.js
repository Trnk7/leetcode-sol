/**
 * // Definition for a _Node.
 * function _Node(val, left, right, next) {
 *    this.val = val === undefined ? null : val;
 *    this.left = left === undefined ? null : left;
 *    this.right = right === undefined ? null : right;
 *    this.next = next === undefined ? null : next;
 * };
 */

/**
 * @param {_Node} root
 * @return {_Node}
 */
var connect = function(root) {
    if (!root) return root;
    let queue = [root];
    let res = root;
    while (queue.length) {
        let len = queue.length;
        let last =null;
        for (let i = 0; i < len; i++) {
            let node = queue.shift();
            node.next=last;
            last = node;
            if (node.right) queue.push(node.right);
            if (node.left) queue.push(node.left);
        }
    }
    return res;
};