class Solution {
public:
    int largestAltitude(vector<int>& gain) {
        int ans =0;
        int sum=0;
        for(auto&h:gain){
            sum+=h;
            ans = max(ans,sum);
        }
        return ans;
    }
};