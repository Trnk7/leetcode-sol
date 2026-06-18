class Solution {
public:
    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int color) {
        int n = image.size();
        int m = image[0].size();

        int sCol = image[sr][sc];

        queue<pair<int,int>> q;
        image[sr][sc]=color;
        q.push({sr,sc});

        int dx[4]={0,0,1,-1};
        int dy[4]={-1,1,0,0};
        vector<vector<bool>> visited(n,vector<bool>(m,0));
        while(!q.empty()){
            int l = q.size();

            while(l--){
                int r = q.front().first;
                int c = q.front().second;
                q.pop();
                for(int i =0;i<4;i++){
                    int nr =r+dx[i];
                    int nc = c+dy[i];
                    if(nr<0||nc<0||nr>=n||nc>=m)continue;

                    if(image[nr][nc]==sCol&&!visited[nr][nc]){
                        visited[nr][nc]=1;
                        image[nr][nc] = color;
                        q.push({nr,nc});
                    }
                }
            }
        }
        return image; 
    }
};