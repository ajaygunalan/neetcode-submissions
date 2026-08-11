class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        state.assign(numCourses, 0);

        for(auto pair :  prerequisites) 
            graph[pair[0]].push_back(pair[1]);

        for(int course=0; course<numCourses; course++) 
            if(!dfs(course)) 
                return false;
                
        return true;
    }
private:
    unordered_map<int, vector<int>> graph;
    vector<int> state;

    bool dfs(int course) {
        if(state[course] == 1) return false;
        if(state[course] == 2) return true;
        state[course] = 1;

        for(int neighbor : graph[course])
            if(!dfs(neighbor))
                return false;

        state[course] = 2;
        return true;
    }
};