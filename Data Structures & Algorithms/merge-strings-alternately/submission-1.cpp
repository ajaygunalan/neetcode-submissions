#include <iostream>
#include <ranges>
#include <string>

class Solution {
public:
    string mergeAlternately(string word1, string word2) {
        string result;
        result.reserve(word1.size() + word2.size());
        size_t n = std::min(word1.size(), word2.size());
        for (auto [a, b] : std::views::zip(word1, word2))
            result += {a, b};
        return result + word1.substr(n) + word2.substr(n);
    }
};