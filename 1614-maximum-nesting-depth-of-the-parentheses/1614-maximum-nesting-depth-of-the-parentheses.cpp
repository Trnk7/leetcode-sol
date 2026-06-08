class Solution {
public:
    int maxDepth(string s) {
        int open=0;
        int ans=0;
        for(int i =0;i<s.length();i++){
            if(s[i]=='('){
                open++;
            ans = max(open,ans);
            }
            if(s[i]==')')open--;
        }
        return ans;
    }
};