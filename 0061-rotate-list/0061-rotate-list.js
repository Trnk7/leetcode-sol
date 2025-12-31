/**
 * Definition for singly-linked list.
 * function ListNode(val, next) {
 *     this.val = (val===undefined ? 0 : val)
 *     this.next = (next===undefined ? null : next)
 * }
 */
/**
 * @param {ListNode} head
 * @param {number} k
 * @return {ListNode}
 */
var rotateRight = function(head, k) {
    if(head==null||k==0)return head;

    let fast = head;
    let slow = head;
    let l=1;
    while (fast.next !== null) {
        fast = fast.next;
        l++;
    }
    fast=head;
    for (let i = 0; i <k%l; i++) {
        
        fast = fast.next;
        if(fast==null){
            fast=head;
        }
    }
    while (fast.next !== null) {
        fast = fast.next;
        slow = slow.next;
    }
    
    if(slow.next==null)return head;
    let newHead = slow.next;
    slow.next=null;
    fast.next=head
    return newHead;
};