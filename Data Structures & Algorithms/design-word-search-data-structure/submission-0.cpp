class WordDictionary {
    struct TrieNode {
        TrieNode* child[26];
        bool isEnd;

        TrieNode() {
            isEnd = false;
            for(int i=0; i<26; i++)
                child[i] = nullptr;
        }
    };
    TrieNode* root;

    bool dfs(TrieNode* current, const string& word, int index) {
        if(index == word.size()) return current->isEnd;

        if(word[index] == '.') {
            for(int i=0; i<26; i++) {
                if(current->child[i] != nullptr && dfs(current->child[i], word, index+1))
                    return true;
            }
            return false;
        }

        int idx = word[index]-'a';
        if(!current->child[idx])
            return false;
        return dfs(current->child[idx], word, index+1);
    }

public:
    WordDictionary() {
        root =  new TrieNode();
    }
    
    void addWord(string word) {
        TrieNode* current = root;
        for(char ch:word) {
            int idx = ch - 'a';
            if(!current->child[idx])
                current->child[idx] = new TrieNode();
            current =  current->child[idx];
        }
        current->isEnd = true;
    }
    
    bool search(string word) {
        return dfs(root, word, 0);
    } 
};