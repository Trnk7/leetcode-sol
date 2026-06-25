class Solution {
public:
    bool rotateString(string s, string goal) {
        s = s+s;
        int j =0;
        for(int i=0;i<s.size();i++){
           if(s[i]==goal[0]){
            for(j=0;j<goal.size();j++){
                if(s[i+j]!=goal[j]){
                    break;
                }
            }
            if(j==goal.size()){
                return true;
            }
           }
        }
        return false;
    }
};