class Solution {
public:
    int characterReplacement(string s, int k) {
        vector<int> count(26, 0);
        int l=0, longest=0, maxCount = 0;

        for(int r=0; r<s.size(); r++) {
            int rightIdx = s[r] - 'A';
            count[rightIdx]++;
            maxCount = max(maxCount, count[rightIdx]);

            int windwLen = r-l+1;
            int replacementNeeded = windwLen - maxCount;

            //invalid window
            while(replacementNeeded > k) {
                int leftIdx = s[l] - 'A';
                count[leftIdx]--;
                l++;

                windwLen = r-l+1;
                replacementNeeded = windwLen - maxCount;
            }
            longest = max(longest, r - l + 1);
        }
        return longest;
    }
};