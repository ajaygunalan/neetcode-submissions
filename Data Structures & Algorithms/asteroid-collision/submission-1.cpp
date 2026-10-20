class Solution {
public:
    vector<int> asteroidCollision(vector<int>& asteroids) {
        vector<int> st;
        for(int a : asteroids) {
            bool alive = true;
            while(alive && !st.empty() && st.back()>0 && a<0) {
                if(abs(a) > st.back()) st.pop_back();
                else if(abs(a) == st.back()) st.pop_back(), alive=false;
                else alive=false;
            }
            if(alive)
                st.push_back(a);
        }
        return st;
    }
};