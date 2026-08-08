class Solution {
private:
    string s;
    int count=0;
    void isPalindrome(int l, int r) {
        while(l >= 0 && r < s.length() && s[l] == s[r]) {
            count++;
            l--;
            r++;
        }
    }
public:
    int countSubstrings(string s) {
        this->s = s;
        for(int i=0; i<s.length(); i++){
            isPalindrome(i, i);
            isPalindrome(i, i+1);
        }
        return count;
    }
};
