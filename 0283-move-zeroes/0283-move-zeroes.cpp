class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int l=0,h=1;
        while(h<nums.size()&&l<nums.size()){
            if(nums[l]!=0){
                l++;
                h=l+1;
                continue;
            }
            if(nums[h]==0){
                h++;
                continue;
            }
            swap(nums[l],nums[h]);
            l++;
            h=l+1;
        }

    }
};