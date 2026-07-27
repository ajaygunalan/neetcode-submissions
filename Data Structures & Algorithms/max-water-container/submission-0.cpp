class Solution {
public:
    int maxArea(vector<int>& heights) {
        int l , r;
        l = 0;
        r = heights.size()-1;
        int maxArea = 0;
        while(l < r) {
            int area = (r-l)*min(heights[l], heights[r]);
            maxArea = max(area, maxArea);
            
            if(heights[l] > heights[r])
                r--;

            else if(heights[l] < heights[r])
                l++;
            
            else 
                l++;

        }
        return maxArea;
    }
};
