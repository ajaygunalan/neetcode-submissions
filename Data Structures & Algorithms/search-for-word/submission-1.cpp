class Solution {
public:
    vector<vector<char>> board_;
    string word_;

    bool dfs(int r, int c, int i) {
        if(i == word_.size()) return true;
        if(r<0 || r>=board_.size() || c<0 || c>=board_[0].size()) return false;
        if(board_[r][c] != word_[i]) return false;

        board_[r][c] = '#';
        bool found =  dfs(r+1, c, i+1) || dfs(r-1, c, i+1)
        || dfs(r, c+1, i+1) || dfs(r, c-1, i+1);
        board_[r][c] = word_[i];

        return found;
    }


    bool exist(vector<vector<char>>& board, string word) {
        word_ = word;
        board_ = board;        
        for(int r=0; r<board_.size(); r++) {
            for(int c=0; c<board_[0].size(); c++)
                if (dfs(r, c, 0)) return true;
        }
        return false; 
    }
};