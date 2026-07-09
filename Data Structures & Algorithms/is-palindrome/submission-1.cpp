class Solution {
public:
    bool isPalindrome(string s) {
        string filtered;
        for (char ch: s) {
            if (isalnum(ch))
                filtered += tolower(ch);
        }
        int j = filtered.length();
        for (int i = 0;  i < filtered.length(); i++) {
            if (filtered[i] !=  filtered[j-1])
                return false;
            j--;
        }
        return true;
    }
};
