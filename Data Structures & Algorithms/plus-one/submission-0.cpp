class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        if(digits.empty())
            return {1};
        
        //normal case of addition
        if(digits.back() <9) {
            digits.back() += 1;
            return digits;
        }
        else {
            //remove the 9
            digits.pop_back();
            //recursive call to next digits 
            vector<int> result = plusOne(digits);
            result.push_back(0);
            return result;
        }
        
    }
};
