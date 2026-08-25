class Solution {
public:
    bool isAlienSorted(vector<string>& words, string order) {

        // build hash map
        unordered_map<char, int> hashMap;
        for(int i=0; i<order.length(); i++) 
            hashMap[order[i]] = i;
    

        int n = words.size();
        for(int i=0; i<n-1; i++) {
            int len = min(words[i].size(), words[i+1].size());
            int j=0;
            while(j<len) {
                if(words[i][j] == words[i+1][j]) {
                    j++;
                    continue;
                } 
                if(hashMap[words[i][j]] > hashMap[words[i+1][j]]) 
                    return false;
                break;
            }
            if(j == len && words[i].size() > words[i + 1].size()) 
                return false;
        }
        return true;
    }
};