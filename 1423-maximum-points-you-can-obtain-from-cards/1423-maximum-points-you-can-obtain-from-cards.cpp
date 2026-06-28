class Solution {
public:
    int maxScore(vector<int>& cardPoints, int k) {
        int l =0;
        int n =cardPoints.size();
        int sum =0;
        int maxSum=0;
        for(l=0;l<k;l++){
            sum+=cardPoints[l];
        }
        maxSum=sum;
        for(int i=0;i<k;i++){
            sum-=cardPoints[k-1-i];
            sum+=cardPoints[n-1-i];
            maxSum=max(sum,maxSum);
        }
        return maxSum;
       
    }
};