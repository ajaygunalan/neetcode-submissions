class Solution {
public:
    int mySqrt(int x) {
        int l=0, r=x;
        long m;
        while(l <= r) {
            m = l + (r-l)/2;
            long long  guess = m*m;
            if(guess == x) return m;
            else if(guess > x) r = m-1; 
            else if(guess < x) l = m+1;
        }
        return m;
    }
};