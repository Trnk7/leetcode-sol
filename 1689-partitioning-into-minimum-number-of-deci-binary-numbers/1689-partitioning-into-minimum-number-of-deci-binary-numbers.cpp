class Solution {
public:
    int minPartitions(string n) {
        int maxnum=0;
        for(int i=0;i<n.size();i++){
            maxnum = max(maxnum,n[i]-'0');
        }
        return maxnum;
    }
};