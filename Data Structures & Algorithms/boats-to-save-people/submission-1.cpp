class Solution {
public:
    int numRescueBoats(vector<int>& people, int limit) {
        ranges::sort(people);
        int count=0;
        int l=0, r=people.size()-1;
        while(l <= r) {
            if(people[l] + people[r] <= limit) l++;
            r--;
            count++;
        }
        return count;
    }
};