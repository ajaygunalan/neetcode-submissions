class Solution {
public:
    vector<int> countBits(int n) {
        vector<int> res;
        for(int i = 0; i<=n; i++)
            res.push_back(hammingWeight(i));
        return res;
    }

    int hammingWeight(uint32_t n) {
        if (n == 0)
            return 0;
        return (n & 1) + hammingWeight(n >> 1);
    }

};
