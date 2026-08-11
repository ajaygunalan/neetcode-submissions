class Solution {
public:
    bool validTree(int n, vector<vector<int>>& edges) {
        // A tree must have exactly n - 1 edges
        if(edges.size() > n-1) return false;

        adj.assign(n, {});
        visit.assign(n, {});

        // Store every undirected edge in both directions
        for(auto edge : edges) {
            adj[edge[0]].push_back(edge[1]);
            adj[edge[1]].push_back(edge[0]);
        }   

        // With n - 1 edges, reaching every node guarantees a tree
        return dfs(0) == n;
    }

private:
    vector<vector<int>> adj;
    vector<bool> visit;

    // Return the number of nodes reached from this node
    int dfs(int node) {
        visit[node] = true;
        int reached = 1;

        for(int neighbor : adj[node])
            if(!visit[neighbor])
                reached += dfs(neighbor);
        return reached;
    }
};