class Solution {
public:
    bool recu(vector<vector<char>>& board, string word,int i,int x,int y){
        if(i>=word.size())return true;
        if(x<0||x>=board.size()||y<0||y>=board[0].size())return false;
        if(board[x][y]!=word[i])return false;
        char temp = board[x][y];
        board[x][y]='$';
        bool res = recu(board,word,i+1,x-1,y) ||
               recu(board,word,i+1,x,y-1) ||
               recu(board,word,i+1,x+1,y) ||
               recu(board,word,i+1,x,y+1);
        board[x][y]=temp;
        return res;
    }
    bool exist(vector<vector<char>>& board, string word) {
        for(int i=0;i<board.size();i++){
            for(int j =0;j<board[0].size();j++){
                    if(recu(board,word,0,i,j)){
                        return true;
                    }
            }
        }
        return false;
    }
};