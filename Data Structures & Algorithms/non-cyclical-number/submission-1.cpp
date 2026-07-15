class Solution {
public:
    bool isHappy(int n) {
        unordered_set<int> seen;

        while(n != 1) {
            if(seen.count(n))
                return false;
            seen.insert(n);
            n = sum_of_square(n);
        }
        return true;
    }

    int sum_of_square(int n) {
        int sum_of_sq = 0;
        while(n > 0) {
            sum_of_sq += (n%10)*(n%10);
            n = n/10;
        }
        return sum_of_sq;
    }


};
