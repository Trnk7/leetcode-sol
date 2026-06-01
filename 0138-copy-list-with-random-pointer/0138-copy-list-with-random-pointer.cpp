/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
*/

class Solution {
public:
    Node* copyRandomList(Node* head) {
        if(head==NULL)return NULL;
        unordered_map<Node*, Node*> mp;
        Node* newHead = new Node(head->val);
        Node* curr = head->next;
        mp[head]=newHead;

        while(curr){
             Node* nwNode = new Node(curr->val);
             mp[curr] = nwNode;
             curr= curr->next;
        }
        curr = newHead;
        while(head){
            curr->next = mp[head->next];
            curr->random = mp[head->random];
            head=head->next;
            curr=curr->next;            
        }
        return newHead;

    }
};