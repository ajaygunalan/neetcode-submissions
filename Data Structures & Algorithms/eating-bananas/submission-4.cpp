class Solution {
public:
    int minEatingSpeed(vector<int>& piles, int h) {
        int l=1, r=ranges::max(piles), ans=r;
        while(l <= r) {
            int m = l + (r-l)/2;
            long long hours = 0;
            for(int p : piles) 
                hours += (p%m == 0) ? p/m : p/m+1;
            if(hours <= h) ans=m, r=m-1;
            else l = m+1;
        }
        return ans;
    }
};
