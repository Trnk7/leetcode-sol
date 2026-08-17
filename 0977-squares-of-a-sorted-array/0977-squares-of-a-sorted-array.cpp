class Solution {
public:
    vector<int> sortedSquares(vector<int>& nums) {
        sort(nums.begin(),nums.end(),[](auto&a,auto&b){
        return abs(a)<abs(b);
    });
        for(int i=0;i<nums.size();i++){
            nums[i]*=nums[i];
        }
        return nums;
    }
};