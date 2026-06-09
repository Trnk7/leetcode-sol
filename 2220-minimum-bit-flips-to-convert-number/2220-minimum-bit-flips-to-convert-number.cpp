class Solution {
public:
    int minBitFlips(int start, int goal) {
        int bits = start ^ goal;
        int ans=0;
        while(bits){
            ans+=bits&1;
            bits = bits>>1;
        }
        return ans;
    }
};