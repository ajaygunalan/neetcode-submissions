class Solution {
private:
    vector<vector<int>> adjacencyList;
    vector<bool> visited;

    bool dfs(int currentNode, int targetNode) {
        if(currentNode == targetNode) return true;
        
        visited[currentNode] =  true;

        for(int neighbor: adjacencyList[currentNode])
            if(!visited[neighbor] && dfs(neighbor, targetNode))
                return true;

        return false;
    }

public:
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        int n = edges.size();
        adjacencyList.assign(n+1, {});
        visited.assign(n+1, false);

        for(const vector<int>& edge : edges) {
            ranges::fill(visited, false);

            if(dfs(edge[0], edge[1]))
                return {edge[0], edge[1]};
            
            adjacencyList[edge[0]].push_back(edge[1]);
            adjacencyList[edge[1]].push_back(edge[0]);
        }
        
    }
};

/** You build the adjacency list one edge at a time. For each edge `[u,v]`, before adding it, run DFS from `u` to check whether `v` is already reachable through the previously added edges. If `v` is reachable, `[u,v]` is the redundant edge, so return it. Otherwise, add the edge in both directions: store `v` in `graph[u]` and `u` in `graph[v]`. **/
