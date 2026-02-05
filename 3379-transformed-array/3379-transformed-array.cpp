class Solution {
public:
    vector<int> constructTransformedArray(vector<int>& nums) {
        int l = nums.size();
        vector<int> res(l,0);
        for(int i=0;i<l;i++){
            int nextI= (l+i+nums[i]%l)%l;
            res[i]=nums[nextI];
        }
        return res;
    }
};