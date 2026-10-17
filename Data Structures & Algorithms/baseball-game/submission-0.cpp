class Solution {
public:
    int calPoints(vector<string>& operations) {
        vector<int> st;
        for(auto ops : operations) {
            switch(ops[0]) {
                case '+':
                    st.push_back(st.end()[-2]+st.end()[-1]);
                    break;
                case 'C':
                    st.pop_back();
                    break;
                case 'D':
                    st.push_back(st.end()[-1]*2);
                    break;
                default:
                    st.push_back(stoi(ops));
                    break;
            } 
        }
        return  ranges::fold_left(st, 0, plus<int>());
    }
};