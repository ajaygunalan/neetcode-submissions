class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int rows=matrix.size(), cols=matrix[0].size();
        int left=0, right=rows*cols-1;
        while(left <= right) {
            int m = left + (right-left)/2;
            int r = m/cols, c = m%cols; 
            if(matrix[r][c] == target) return true;
            else if(matrix[r][c] > target) right = m-1;
            else if(matrix[r][c] < target) left = m+1; 
        }
        return false;
    }
};
