class Solution {
private:
    vector<string> result;
    string path;
    string* digitsPtr;

    const vector<string> table = {"", "", "abc", "def", "ghi",
    "jkl", "mno", "pqrs", "tuv", "wxyz"};

    void backtrack(int g) {
        string& digits = *digitsPtr;

        if(g == digits.size()) {
            result.push_back(path);
            return;
        }

        const string& letters = table[digits[g]-'0'];
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