class Solution {
public:
    int countDigitOccurrences(vector<int>& nums, int digit) {
        int ans=0;
        char d = digit+'0';
        for(int n:nums){
            string num = to_string(n);
            int i=0;
            while(i<num.size()){
                if(num[i]==d){
                    ans++;
                }
                i++;
            }
        }
        return ans;
    }
};