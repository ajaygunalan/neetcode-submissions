// class Solution {
// public:
//     bool isAnagram(string s, string t) {
//         if (s.length() != t.length())
//             return false;
//         unordered_map<char, int> sCount;
//         unordered_map<char, int> tCount;
//         for (int i=0; i < s.length(); i++){
//             sCount[s[i]]++;
//             tCount[t[i]]++;
//         }
//         return sCount == tCount;
        
//     }
// };




class Solution {
    public:
        bool isAnagram(string& s, string& t) {
            unordered_map<char, int> map;

            if(s.length() !=  t.length())
                return false;

            for (char ch : s)  
                map[ch]++;

            for (char ch : t) 
                map[ch]--;
            

            for (auto p : map) 
                if (p.second != 0) 
                    return false;

            return true;
        }

};


































