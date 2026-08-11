class Solution {
public:
    int countComponents(int n, vector<vector<int>>& edges) {
        adj.assign(n, {});
        visit.assign(n, false);

        for(auto edge :  edges) {
            adj[edge[0]].push_back(edge[1]);
            adj[edge[1]].push_back(edge[0]);
        }

        int components = 0;
        for(int node=0; node<n; node++) {
            if(visit[node]) 
                continue;
            components++;
            dfs(node);
        }
        return components;
    }    

private:    
    vector<vector<int>> adj;
    vector<bool> visit;
    
    void dfs(int node) {
        visit[node] = true;
        for(auto neighbor : adj[node])
            if(!visit[neighbor])
                dfs(neighbor);
    }
};