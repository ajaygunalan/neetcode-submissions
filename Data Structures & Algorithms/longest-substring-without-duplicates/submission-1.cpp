class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int l=0, maxLen = 0;
        unordered_set<char> seen;

        for(int r = 0; r < s.length(); r++) {
            while(seen.count(s[r])) {
                seen.erase(s[l]);
                l++;
            }
            seen.insert(s[r]);
            maxLen =  max(maxLen, r-l+1);
        }
        return maxLen;
    }
};