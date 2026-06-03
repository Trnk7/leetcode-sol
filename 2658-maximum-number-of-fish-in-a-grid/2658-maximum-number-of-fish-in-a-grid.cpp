class Solution {
public:
    int findMaxFish(vector<vector<int>>& board) {
        int maxFish=0;
        for(int i=0;i<board.size();i++){
            for(int j = 0;j<board[i].size();j++){
                if(!board[i][j])continue;
                maxFish = max(maxFish,explore(i,j,board));
            }
        }
        return maxFish;
    }
    
    int explore(int i,int j,vector<vector<int>>& board,int noOfFish=0){
        if(!board[i][j])return noOfFish;
        noOfFish+=board[i][j];
        board[i][j]=0;
        if(i>0)noOfFish+=explore(i-1,j,board);
        if(j>0)noOfFish+=explore(i,j-1,board);
        if(i<board.size()-1)noOfFish+=explore(i+1,j,board);
        if(j<board[i].size()-1)noOfFish+=explore(i,j+1,board);
        return noOfFish;
    }
};