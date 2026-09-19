class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        int n=nums.size();
        k = k%n;
        rev(nums,0,n);
        rev(nums,0,k);
        rev(nums,k,n);
    }
    void rev(vector<int>& nums, int l,int h){
        for(int i=0;i<(h-l)/2;i++){
            swap(nums[l+i],nums[h-1-i]);
        }
    }
};