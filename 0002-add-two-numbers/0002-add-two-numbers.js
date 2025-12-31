/**
 * Definition for singly-linked list.
 * function ListNode(val, next) {
 *     this.val = (val===undefined ? 0 : val)
 *     this.next = (next===undefined ? null : next)
 * }
 */
/**
 * @param {ListNode} l1
 * @param {ListNode} l2
 * @return {ListNode}
 */
var addTwoNumbers = function(l1, l2) {
    let recu = (l1,l2,carry=0)=>{
        if(!l1&&!l2&&!carry){
            return null
        }
        const newval = (l1?.val||0)+(l2?.val||0)+carry
        next = recu(l1?.next,l2?.next,Math.floor(newval/10))
        return new ListNode(newval%10,next)
    }
    return recu(l1,l2)
};