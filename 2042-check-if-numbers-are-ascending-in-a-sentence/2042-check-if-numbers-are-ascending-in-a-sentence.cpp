class Solution {
public:
    bool areNumbersAscending(string s) {
        int last=0;
        int i=0;
        while(i<s.size()){
            int n=0;
            if(s[i]>'0'&&s[i]<='9'){
                if(s[i+1]>='0'&&s[i+1]<='9'){
                    n = (s[i]-'0')*10+s[i+1]-'0';
                    i++;
                }else{
                    n = s[i]-'0';
                }
            }else{
                i++;
                continue;
            }
            cout<<n<<" "<<last<<'\n';
            if(n>last){
                last=n;
            }else{
                return false;
            }
            i++;
        }
        return true;
    }
};