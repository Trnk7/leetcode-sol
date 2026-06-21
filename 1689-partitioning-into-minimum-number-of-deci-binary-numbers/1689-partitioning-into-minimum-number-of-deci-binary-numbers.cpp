class Solution {
public:
    int minPartitions(string n) {
        int maxnum=0;
        for(char&c:n){
            maxnum = max(maxnum,c-'0');
        }
        return maxnum;
    }
};