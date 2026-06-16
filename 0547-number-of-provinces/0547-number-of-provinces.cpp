class Solution {
public:
    
    int findCircleNum(vector<vector<int>>& isConnected) {
        int n = isConnected.size();
        vector<vector<int>> adj(n);
        for(int i =0;i<n;i++){
            for(int j =i+1;j<n;j++){
                if(isConnected[i][j]){
                    adj[i].push_back(j);
                    adj[j].push_back(i);
                }
            }
        }
        vector<bool> visited(n,0);
        int ans=0;
        for(int i =0;i<n;i++){
            if(!visited[i]){
                ans++;
                visit(i,adj,visited);
            }
        }
        return ans;
    }
    void visit(int node,vector<vector<int>>&adj,vector<bool>&visited){
        visited[node]=true;
        cout<<node<<'\n';
        for(auto n: adj[node]){
            if(!visited[n])visit(n,adj,visited);
        }
    }
};