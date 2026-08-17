class Solution {
public:
    vector<int> sortedSquares(vector<int>& nums) {
        int n = nums.size();
        int l=-1,r=n;
        for(int i=0;i<n;i++){
            if(nums[i]<0){
                l++;
            }else{
                r--;
            }
        }
        vector<int> sqrs;
        for(int i =0;i<n;i++){
            if(l>=0&&r<n){
                if(nums[l]*nums[l]<nums[r]*nums[r]){
                    sqrs.push_back(nums[l]*nums[l]);
                    l--;
                }else{
                    sqrs.push_back(nums[r]*nums[r]);
                    r++;
                }
                continue;
            }
            if(l>=0){
                sqrs.push_back(nums[l]*nums[l]);
                l--;
            }
            if(r<n){
                sqrs.push_back(nums[r]*nums[r]);
                r++;
            }
            
        }
        return sqrs;
    }
};