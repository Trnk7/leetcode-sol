class Solution {
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>>ans;
        helper(candidates,{},0,target,ans);
        return ans;
    }
    void helper(vector<int>&cand,vector<int>curr,int st,int target,vector<vector<int>>&ans){
        if(target == 0){
            ans.push_back(curr);
            return;
        }
        for(int i =st;i<cand.size();i++){
            if(cand[i]<=target){
                curr.push_back(cand[i]);
                helper(cand,curr,i,target-cand[i],ans);
                curr.pop_back();
            }
        }
    }
};