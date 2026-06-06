class Solution {
public:
    int minEatingSpeed(vector<int>& piles, int h) {
        int high = *max_element(piles.begin(),piles.end());
        int low = 1;
        int ans =high;

        while(low<=high){
            int mid = low+(high-low)/2;
            long int totalH = checkSpeed(piles,mid);
            if(totalH<=h){
                high=mid-1;
                ans=mid;
            }else{
                low=mid+1;
            }
        }
        return ans;

    }
    long int checkSpeed(vector<int>&piles,int speed){
        long int totalH =0;
        for(int i: piles){
            totalH+=ceil((double(i)/speed));
        }
        return totalH;
    }
};