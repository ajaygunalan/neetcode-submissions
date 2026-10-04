// class Solution {
// public:
//     int majorityElement(vector<int>& nums) {
//         unordered_map<int, int> countMap;
//         int maxCount = nums.size()/2, result=0;
//         for(int num : nums) {
//             countMap[num]++;
//             if(countMap[num] > maxCount)
//                 result = num;
//         }
//         return result; 
//     }
// };

class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int candidate=0, count=0;
        for(int num : nums) {
            if(count == 0) candidate = num;
            count += (num == candidate) ? 1 : -1;
        }
        return candidate; 
    }
};