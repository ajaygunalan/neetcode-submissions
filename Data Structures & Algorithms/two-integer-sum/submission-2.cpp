class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> seen;
        for (int i = 0; i < nums.size(); i++) {
            //find the complement
            int complement = target - nums[i];
            
            //check if complement is present in hashmap
            if(seen.count(complement))
                return {seen[complement], i};
            
            //if no complement, insert the key which is the number and index which is value
            seen[nums[i]] = i;
        }
        return {};
    }
};