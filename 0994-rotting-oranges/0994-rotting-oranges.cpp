class Solution {
public:
    int orangesRotting(vector<vector<int>>& grid) {
        int total = 0;
        int time =0;
        int rotten =0;
        queue<pair<int,int>> q;
        int m = grid.size();
        int n = grid[0].size();

        for(int i =0;i<m;i++){
            for(int j = 0;j<n;j++){
                if(grid[i][j]==2){
                    q.push({i,j});
                }
                if(grid[i][j]!=0){
                    total++;
                }
            }
        }
        int dx[4] = {0, 0, 1, -1};
        int dy[4] = {1, -1, 0, 0};

        while(!q.empty()){
            int l = q.size();
            rotten+=l;
            while(l--){
                int x = q.front().first;
                int y = q.front().second;
                q.pop();
                for(int k=0;k<4;k++){
                    int nx = x+dx[k];
                    int ny = y+dy[k];

                    if (nx < 0 || ny < 0 || nx >= m || ny >= n || grid[nx][ny] != 1)continue;

                    grid[nx][ny]=2;
                    q.push({nx,ny});
                }
            }
            if(!q.empty()){
                time++;
            }
        }
        return total==rotten?time:-1;
        
    }
};