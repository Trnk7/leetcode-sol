class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int maxs =INT_MIN;
        int curs = 0;
        for(int i :nums){
            curs+=i;
            maxs = max(curs,maxs);
            if(curs<0){
                curs=0;
            };
        };
        return maxs;

    }
};