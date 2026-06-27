using Board = vector<vector<char>>;
class Solution {
public:
    bool isValid(Board&board,int x,int y,char c){
        for(int i =0;i<9;i++){
            if(board[i][y]==c)return false;
        }
        for(int i =0;i<9;i++){
            if(board[x][i]==c)return false;
        }
        int rBox = 3*(x/3);
        int cBox = 3*(y/3);

        for(int i=0;i<3;i++){
            for(int j =0;j<3;j++){
                if(board[rBox+i][cBox+j]==c)return false;
            }
        }
        return true;
    }
    bool recu(Board& board){
        for(int i =0;i<9;i++){
            for(int j =0;j<9;j++){
                if(board[i][j]=='.'){
                    for(char c='1';c<='9';c++){
                        if(isValid(board,i,j,c)){
                            board[i][j]=c;
                            if(recu(board))return true;
                            board[i][j]='.';
                        }
                    }
                    return false;
                }
            }
        }
        return true;
    }
    void solveSudoku(Board& board) {
        recu(board);
    }
};