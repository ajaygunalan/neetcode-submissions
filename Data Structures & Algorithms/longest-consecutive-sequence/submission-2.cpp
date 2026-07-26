class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        unordered_set<int> setMap(nums.begin(), nums.end());

        int longest = 0;

        for (int num : nums) {
            // if num-1 exist it is mid term 
            if(setMap.count(num-1))
                continue;
            
            int length = 1;

            // if it is started term count its length
            while(setMap.count(num + length))
                length++;

            longest = max(length, longest);
        }
        return longest;
    }
};