/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    vector<vector<int>> spiralMatrix(int m, int n, ListNode* head) {
        vector<vector<int>> mat(m,vector<int>(n,-1));

        int i =0;
        int j=0;
        int di=0;
        int dj=1;
        while(head){
            mat[i][j]=head->val;
            head=head->next;
            if(i+di<0||j+dj<0||i+di>=m||j+dj>=n||mat[i+di][j+dj]!=-1){
                int t = dj;
                dj = -di;
                di=t;
            }
            i+=di;
            j+=dj;
        }
        return mat;
    }
};