class PrefixTree {
private: 
    struct TrieNode {
        TrieNode* child[26];
        bool isEnd;

        TrieNode() {
            isEnd = false;
            for (int i=0; i<26; i++)
                child[i] = nullptr;
        }
    };
    TrieNode* root;

public:
    PrefixTree() {
        root = new TrieNode();
    }
    
    void insert(string word) {
        TrieNode* current = root;
        for(char ch : word) {
            int idx = ch - 'a';
            if(!current->child[idx])
                current->child[idx] = new TrieNode();
            current = current->child[idx];
        }
        current->isEnd =true;
    }
    
    bool search(string word) {
        TrieNode* current = root;
        for(char ch : word) {
            int idx = ch - 'a';
            if(!current->child[idx])
                return false;
            current = current->child[idx];
        }
        return current->isEnd;
    }
    
    bool startsWith(string prefix) {
        TrieNode* current = root;
        for(char ch : prefix) {
            int idx = ch - 'a';
            if(!current->child[idx])
                return false;
            current = current->child[idx];
        }
        return true;
    }
};
