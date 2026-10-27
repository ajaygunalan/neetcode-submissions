class Solution {
public:
    int shipWithinDays(vector<int>& weights, int days) {
        int l=0, r=0;
        for(int w : weights) l=max(l,w), r += w;
        while(l < r) {
            int m =  l + (r-l)/2;
            int load=0, count=1;           
            for(int w :  weights){
                if(load + w > m) count++, load=0;
                load += w;
            }
            if(count <= days) r=m;
            else l = m+1;
        }
        return l;
    }
};