class Solution {
public:
    bool isValid(string s) {
        std::stack<char> brackets;
        unordered_map<char, char> match;
        match = {
            {')','('},
            {']','['},
            {'}','{'}
        };
        for (char ch : s) {
            if (ch == '(' || ch == '[' || ch == '{') {
                brackets.push(ch);
            }
            else {
                if (brackets.empty() || brackets.top() != match[ch])
                    return false;
                brackets.pop();
            }

        }
        return brackets.empty();
        
    }
};