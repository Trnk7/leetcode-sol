class Solution {
public:
    bool lemonadeChange(vector<int>& bills) {
        if(bills[0]!=5)return false;
        int coin[] = {5,0};


        for(int i =1;i<bills.size();i++){
            if(bills[i]==5){
                coin[0]+=5;
            }else if(bills[i]==10){
                if(coin[0]>0){
                    coin[0]-=5;
                    coin[1]+=10;
                }else{
                    return false;
                }
            }else{
                if(coin[0]>=5&&coin[1]>=10){
                    coin[0]-=5;
                    coin[1]-=10;
                }else if(coin[0]>=15){
                    coin[0]-=15;
                }else{
                    return false;
                }
            }
        }
        return true;
    }
};