class Solution {
public:
    int countAliveNeighbour(int &i,int& j,vector<vector<int>>& board){
        int c=0;
        if(i>0&&abs(board[i-1][j])==1){
            c++;
        }
        if(j>0 && abs(board[i][j-1])==1){
            c++;
        }
        if(i>0&j>0 && abs(board[i-1][j-1])==1){
            c++;
        }
        if(i>0&&j<board[i].size()-1&&abs(board[i-1][j+1])==1){
            c++;
        }
        if(j>0&&i<board.size()-1&&abs(board[i+1][j-1])==1){
            c++;
        }
        if(i<board.size()-1&&abs(board[i+1][j])==1){
            c++;
        }
        if(j<board[i].size()-1&&abs(board[i][j+1])==1){
            c++;
        }
        if(i<board.size()-1&&j<board[i].size()-1&&abs(board[i+1][j+1])==1){
            c++;
        }
        return c;
    }
    void gameOfLife(vector<vector<int>>& board) {
        for(int i=0;i<board.size();i++){
            for(int j=0;j<board[i].size();j++){
                int n = countAliveNeighbour(i,j,board);
                if((n<2||n>3)&& board[i][j]==1){
                    board[i][j]=-1;
                }
                if(n==3&&board[i][j]==0){
                    board[i][j]=2;
                }
            }
        }
        for(int i=0;i<board.size();i++){
            for(int j=0;j<board[i].size();j++){
                switch(board[i][j]){
                    case 2:
                    board[i][j]=1;
                    break;
                    case -1:
                    board[i][j]=0;
                    break;
                }
            }
        }
    }

};