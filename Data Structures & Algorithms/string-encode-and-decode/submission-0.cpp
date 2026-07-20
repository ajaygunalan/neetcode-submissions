class Solution {
public:

    string encode(vector<string>& strs) {
        string res;
        for(auto& word : strs){
            res += to_string(word.length())+"#"+ word; 
        }
        return res;
    }

    vector<string> decode(string s) {
        vector<string> res;
        int i=0;
        while(i < s.size()) {
            // Find the # delimiter
            int j = i;
            while (s[j] != '#')
                j++;
            
            // Extract length from position i to j
            int len = stoi(s.substr(i, j - i));
 
            //push the word
            res.push_back(s.substr(j+1, len));
            
            // Move pointer past this string
            i = j + 1 + len;
        }
        return res;
    }
};
