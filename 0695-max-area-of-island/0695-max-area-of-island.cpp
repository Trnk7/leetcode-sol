class Solution {
public:
    int maxAreaOfIsland(vector<vector<int>>& board) {
        int maxArea=0;
        for(int i=0;i<board.size();i++){
            for(int j = 0;j<board[i].size();j++){
                if(!board[i][j])continue;
                maxArea = max(maxArea,explore(i,j,board));
            }
        }
        return maxArea;
    }
    
    int explore(int i,int j,vector<vector<int>>& board,int area=0){
        if(!board[i][j])return area;
        board[i][j]=0;
        area++;
        if(i>0)area+=explore(i-1,j,board);
        if(j>0)area+=explore(i,j-1,board);
        if(i<board.size()-1)area+=explore(i+1,j,board);
        if(j<board[i].size()-1)area+=explore(i,j+1,board);
        return area;
    }
};