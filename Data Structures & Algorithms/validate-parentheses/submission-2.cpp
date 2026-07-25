// class Solution {
// public:
//     bool isValid(string s) {
//         std::stack<char> brackets;
//         unordered_map<char, char> match;
//         match = {
//             {')','('},
//             {']','['},
//             {'}','{'}
//         };
//         for (char ch : s) {
//             if (ch == '(' || ch == '[' || ch == '{') {
//                 brackets.push(ch);
//             }
//             else {
//                 if (brackets.empty() || brackets.top() != match[ch])
//                     return false;
//                 brackets.pop();
//             }

//         }
//         return brackets.empty();
        
//     }
// };



class Solution {
public:
    bool isValid(string s) {
        stack<char> st;
        unordered_map<char, char> match =  {
            {')', '('}, {']', '['}, {'}','{'}
        };

        for (char ch : s) {
            if(!match.count(ch))
                st.push(ch);
            else {
                if (st.empty() || st.top() != match[ch]) 
                    return false;
                st.pop();
            }      
        }
        return st.empty();
    }
};



































