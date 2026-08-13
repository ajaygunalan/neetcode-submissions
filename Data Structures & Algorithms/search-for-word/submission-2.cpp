class Solution {
private:
    vector<vector<char>>* g;
    string word;
    int rows;
    int cols;

    bool dfs(int r, int c, int i) {
        vector<vector<char>>& board = *g;      // local alias, zero cost
        if (i == word.size()) return true;
        if(r<0 || r>=rows || c<0 || c>=cols || board[r][c] == '#') return false;
        if(board[r][c] != word[i]) return false;
        
        char original = board[r][c];
        board[r][c] = '#'; //visted so mark it
        bool found = dfs(r+1, c, i+1) || 
            dfs(r-1, c, i+1) || 
            dfs(r, c+1, i+1) || 
            dfs(r, c-1, i+1);
        board[r][c] = original; //unmark it
        return found;
    }

public:
    bool exist(vector<vector<char>>& board, string word) {
        g = &board;
        this->word = move(word);
        rows = board.size();
        cols = board[0].size();

        for(int r=0; r<rows; r++)
            for(int c=0; c<cols; c++)
                if(dfs(r, c, 0)) return true;
        return false; 
    }
};
