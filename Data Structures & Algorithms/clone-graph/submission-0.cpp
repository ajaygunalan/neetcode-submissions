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
    unordered_map<Node*, Node*> oldToNew;

    Node* cloneNode(Node* oldNode) {
        //Already cloned: return the exisiitng new node
        if(oldToNew.count(oldNode)) return oldToNew[oldNode];

        // create and remember the new node
        Node* newNode = new Node(oldNode->val);
        oldToNew[oldNode] = newNode;

        //clone and connect evvery neighnor
        for(Node* oldNeighbor : oldNode->neighbors) {
            Node* newNeighbor = cloneNode(oldNeighbor);
            newNode->neighbors.push_back(newNeighbor);
        }

        return newNode;
    }

public:
    Node* cloneGraph(Node* node) {
        if(!node)
            return {};
        
        oldToNew.clear();
        return cloneNode(node);
    }
};
