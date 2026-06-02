class Solution {
public:
    int countBattleships(vector<vector<char>>& board) {
        int noOfShips=0;
        for(int i=0;i<board.size();i++){
            for(int j = 0;j<board[i].size();j++){
                if(board[i][j]=='.')continue;
                if(i>0){
                    if(j>0){
                        if(board[i-1][j]=='.'&&board[i][j-1]=='.'){
                            noOfShips++;
                        }
                    }else if(board[i-1][j]=='.'){
                        noOfShips++;
                    }
                }else{
                    if(j>0){
                        if(board[i][j-1]=='.'){
                            noOfShips++;
                        }
                    }else{
                        if(board[i][j]=='X'){
                            noOfShips++;
                        }
                    }
                }
            }
        }
        return noOfShips;
    }
};