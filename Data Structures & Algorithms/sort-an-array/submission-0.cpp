class Solution {
public:
    vector<int> sortArray(vector<int>& nums) {
        mergeSort(nums, 0, nums.size() - 1);
        return nums;
    }
private:
    void mergeSort(vector<int>& nums, int left, int right) {
        if((right - left) < 1) return;
        int middle = left + (right - left)/2;
        mergeSort(nums, left, middle);
        mergeSort(nums, middle+1, right);
        merge(nums, left, middle, right); 
    }

    void merge(vector<int>& nums, int left, int middle, int right) {
        int i=left, j=middle+1;
        vector<int> temp;

        while(i <= middle && j <= right) {
            if(nums[i] <= nums[j])
                temp.push_back(nums[i++]);
            else
                temp.push_back(nums[j++]);
        } 

        while(i <= middle)
            temp.push_back(nums[i++]);
        while(j <= right)
            temp.push_back(nums[j++]);

        for(int k=0; k<temp.size(); k++)
            nums[left + k] = temp[k];
    }

};