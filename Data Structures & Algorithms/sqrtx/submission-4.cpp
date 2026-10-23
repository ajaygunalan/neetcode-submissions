class Solution {
public:
    int mySqrt(int x) {
        int l=0, r=x;
        while(l <= r) {
            long m = l + (r-l)/2;
            if(m*m <= x) l = m+1;            
            else r=m-1;
            // if(guess == x) return m;
            // else if(guess > x) r = m-1; 
            // else if(guess < x) l = m+1;
        }
        return r;
    }
};