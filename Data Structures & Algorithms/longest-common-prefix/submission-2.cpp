class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        string result;
        for(int i=0; i<strs[0].size(); i++) {
            int str=0;
            for(str; str<strs.size(); str++) 
                if(strs[str][i] != strs[0][i])
                    return result;
                result += strs[0][i];
        }
        return result;
    }
};