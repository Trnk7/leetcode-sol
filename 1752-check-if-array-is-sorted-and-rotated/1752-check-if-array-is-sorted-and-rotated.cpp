class Solution {
public:
    bool check(vector<int>& nums) {
        if(nums.size()<2)return true;
        int asc=0;
        for(int i=0;i<nums.size();i++){
            int j = (i+1)%nums.size();
            if(nums[i]>nums[j]){
                asc++;
            }
            
        }
        return asc<=1;
    }
};