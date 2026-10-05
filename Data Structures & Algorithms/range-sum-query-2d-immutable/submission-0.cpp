class NumMatrix {
public:
    NumMatrix(vector<vector<int>>& matrix) {
        int rows = matrix.size();
        int cols =  matrix[0].size();
        prefixMatrix.assign(rows+1, vector<int>(cols+1, 0));

        for(int r=0; r<rows; r++) 
            for(int c=0; c<cols; c++) 
                prefixMatrix[r+1][c+1] = matrix[r][c] 
                + prefixMatrix[r][c+1] 
                + prefixMatrix[r+1][c] 
                - prefixMatrix[r][c];
            
    }
    
    int sumRegion(int row1, int col1, int row2, int col2) {
        int big = prefixMatrix[row2+1][col2+1];
        int above = prefixMatrix[row1][col2+1];
        int left = prefixMatrix[row2+1][col1];
        int corner = prefixMatrix[row1][col1];
        return big - above - left + corner;
    }



private:
    vector<vector<int>> prefixMatrix;
};

/**
 * Your NumMatrix object will be instantiated and called as such:
 * NumMatrix* obj = new NumMatrix(matrix);
 * int param_1 = obj->sumRegion(row1,col1,row2,col2);
 */