class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        for(int i=0; i<strs[0].size(); i++) {
            for(int str=0; str<strs.size(); str++) 
                if(strs[str][i] != strs[0][i])
                    return strs[0].substr(0,i);
        }
        return strs[0];
    }
};