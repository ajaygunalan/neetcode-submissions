class Solution {
private:
    vector<string> result;
    string path;
    string* digitsPtr;

    unordered_map<char, string> table = {
        {'2', "abc"}, {'3', "def"}, {'4', "ghi"}, {'5', "jkl"},
        {'6', "mno"}, {'7', "pqrs"}, {'8', "tuv"}, {'9', "wxyz"}
    };

    void backtrack(int g) {
        string& digits = *digitsPtr;

        if(g == digits.size()) {
            result.push_back(path);
            return;
        }

        string& letters = table[digits[g]];
        for(int i=0; i<letters.size(); i++) {
            path.push_back(letters[i]);
            backtrack(g+1);
            path.pop_back();
        }

    }

public:
    vector<string> letterCombinations(string digits) {
        if(digits.empty()) return {};
        digitsPtr = &digits;
        backtrack(0);
        return result;
    }
};


// class Solution {
// private:
//     vector<vector<char>> result;
//     vector<char> path;
//     vector<vector<char>>* groupPtr;

//     void backtrack(int g) {
//         vector<vector<char>>& group = *groupsPtr;

//         if(g == groups.size()){
//             result.push_back(path);
//             return;
//         }

//         for(int i=0; i<groups[0].size(); i++) {
//             path.push_back(groups[g][i]);
//             backtrack(g+1);
//             path,pop_back();
//         }
//     }

// public:
//     vector<vector<char>> product(vector<vector<char>>& groups){
//         groupsPtr = &groups;
//         backtrack(0);
//         return result;
//     }
// }