class Solution {
public:
    bool lemonadeChange(vector<int>& bills) {
        if(bills[0]!=5)return false;
        int total5=5;
        int total10=0;


        for(int i =1;i<bills.size();i++){
            if(bills[i]==5){
                total5+=5;
            }else if(bills[i]==10){
                if(total5>0){
                    total5-=5;
                    total10+=10;
                }else{
                    return false;
                }
            }else{
                if(total5>=5&&total10>=10){
                    total5-=5;
                    total10-=10;
                }else if(total5>=15){
                    total5-=15;
                }else{
                    return false;
                }
            }
        }
        return true;
    }
};