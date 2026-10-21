class Solution {
public:
    string simplifyPath(string path) {
        vector<string> st;
        string result;

        stringstream ss(path);
        string part;
        while(getline(ss, part, '/')) {
            if(part == "" || part == ".") continue;
            if(part != "..") st.push_back(part); 
            else if(!st.empty()) st.pop_back();
        }

        for(auto word : st)
            result += "/" + word;

        return result.empty() ? "/" : result;
    }
};