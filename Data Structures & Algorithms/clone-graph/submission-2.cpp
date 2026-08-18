/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};
*/

class Solution {
private:
    unordered_map<Node*, Node*> hashMap;

    void dfs(Node* node) {
        if(!node) return;
        if(hashMap.contains(node)) return;

        Node* newNode =  new Node;
        newNode->val = node->val;
        hashMap[node] = newNode;

        for(auto nodeNext : node->neighbors)
            dfs(nodeNext);
    }


public:
    Node* cloneGraph(Node* node) {
        dfs(node);
        for(auto [oldNode, cloneNode] : hashMap) 
            for(auto oldNext : oldNode->neighbors)
                cloneNode->neighbors.push_back(hashMap[oldNext]);
        return hashMap[node];
    }
};
