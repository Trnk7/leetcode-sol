class Solution {
public:
    int numIslands(vector<vector<char>>& board) {
        int noOfIsland=0;
        for(int i=0;i<board.size();i++){
            for(int j = 0;j<board[i].size();j++){
                if(board[i][j]=='0')continue;
                noOfIsland++;
                explore(i,j,board);

            }
        }
        return noOfIsland;
    }
    
    void explore(int i,int j,vector<vector<char>>& board){
        if(board[i][j]=='0')return;
        board[i][j]='0';
        if(i>0)explore(i-1,j,board);
        if(j>0)explore(i,j-1,board);
        if(i<board.size()-1)explore(i+1,j,board);
        if(j<board[i].size()-1)explore(i,j+1,board);
    }
};