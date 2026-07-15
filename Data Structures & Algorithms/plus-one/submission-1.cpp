class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {

        //edge case of al 999 -> 99 ->9 -> 1 the 0 will be added as recurse from doen to top 
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
