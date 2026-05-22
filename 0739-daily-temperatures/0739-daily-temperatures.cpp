class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temp) {
        stack<int> s;
        int i = temp.size()-1;
        vector<int> answer(i+1);
        answer[i]=0;
        s.push(i);
        while(i>=0){
        while(!s.empty()&&temp[s.top()]<=temp[i]){
            s.pop();
        }
        if(s.empty()){
            answer[i]=0;
        }
        else{
            answer[i]=s.top()-i;
        }
        s.push(i);
        i--;
        }

        return answer;
    }
};