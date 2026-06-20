class Solution {
public:
    vector<vector<int>>all;
    
    vector<vector<int>> permute(vector<int>& nums) {
        vector<int>curr;
        vector<int>visited(nums.size());
        recu(0,curr,nums,visited);
        return all;
        
    }
    void recu(int i ,vector<int>&curr,vector<int>&nums,vector<int>&visited){
        if(curr.size()==nums.size()){
            all.push_back(curr);
            return;
        }
        for(int j = 0;j<nums.size();j++){
            if(visited[j]!=1){
                curr.push_back(nums[j]);
                visited[j]=1;
                recu(i+1,curr,nums,visited);
                curr.pop_back();
                visited[j]=0;
            }
        }
    }
};