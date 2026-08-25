#include <algorithm>
#include <ranges>
#include <string>
#include <unordered_map>
#include <vector>

class Solution {
public:
    bool isAlienSorted(vector<string>& words, string order) {
        unordered_map<char, int> hashMap;
        for(int i=0; i<order.length(); i++) hashMap[order[i]] = i;
        
        for(auto const& [w1, w2] :  words | views::adjacent<2>) {
            size_t len = min(w1.size(), w2.size());
            size_t j=0;
            while(j<len && w1[j] == w2[j] ) j++;
            if(j == len && w1.size() > w2.size()) return false;
            else if(hashMap[w1[j]] > hashMap[w2[j]]) return false;
        }
        return true;
    }
};