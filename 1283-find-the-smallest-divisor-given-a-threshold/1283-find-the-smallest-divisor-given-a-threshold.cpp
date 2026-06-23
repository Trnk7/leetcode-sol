class Solution {
public:
    int sumAfterDiv(vector<int>&nums,int divisor){
        int total=0;
        for(auto&i:nums){
            total+=ceil((double)i/divisor);
        }
        return total;
    }
    int smallestDivisor(vector<int>& nums, int threshold) {
        int l =1;
        int h = INT_MIN;
        for(int&n:nums){
            h = max(h,n);
        }
        int ans =0;
        while(l<=h){
            int mid = l+(h-l)/2;
            int sum = sumAfterDiv(nums,mid);
            if(sum<=threshold){
             h = mid-1;
             ans = mid;   
            }else{
                l=mid+1;
            }
        }
        return ans;
    }
};