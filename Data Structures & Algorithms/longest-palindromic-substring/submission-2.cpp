class Solution {

private:
    string s;
    int start = 0;
    int maxLength = 0;
    void isPalindrome(int l, int r) {
        while(l >= 0 && r < s.length() && s[l] ==  s[r]) {
            int currentLength = r-l+1;
            if(currentLength > maxLength) {
                start = l;
                maxLength = currentLength;
            }
            l--;
            r++;
        }

    }
public:
    string longestPalindrome(string s) {
        this->s = s;

        for(int i=0; i<s.length(); i++){
            isPalindrome(i, i);
            isPalindrome(i, i+1);
        }
        return s.substr(start, maxLength);
    }
};
