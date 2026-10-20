class Solution {
public:
    vector<int> asteroidCollision(vector<int>& asteroids) {
        vector<int> st;
        for(int i=0; i<asteroids.size(); i++) {
            bool alive = true;
            while(alive && !st.empty() && st.back()>0 && asteroids[i]<0) {
                if(abs(asteroids[i]) > st.back()) st.pop_back();
                else if(abs(asteroids[i]) == st.back()) st.pop_back(), alive=false; 
                else alive=false;
            }
            if(alive)
                st.push_back(asteroids[i]);
        }
        return st;
    }
  };