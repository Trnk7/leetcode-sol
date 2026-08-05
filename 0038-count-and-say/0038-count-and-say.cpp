class Solution {
public:
    vector<pair<int,char>> count(const string&s){
        char curr = s[0];
        int freq=0;
        vector<pair<int,char>> ans;
        for(int i=0;i<s.size();i++){
            if(s[i]==curr){
                freq++;
            }else{
                pair<int,char> p(freq,curr);
                ans.push_back(p);
                curr = s[i];
                freq=1;
            }
        }
        pair<int,char> p(freq,curr);
        ans.push_back(p);
        return ans;
    }
    string convert(const vector<pair<int,char>>&arr){
        string ans="";
        for(int i=0;i<arr.size();i++){
            ans = ans+char(arr[i].first+'0')+arr[i].second;
        }
        return ans;
    }
    string countAndSay(int n) {
        string res="1";
        for(int i=1;i<n;i++){
            res = convert(count(res));
        }
        return res;
    }
};