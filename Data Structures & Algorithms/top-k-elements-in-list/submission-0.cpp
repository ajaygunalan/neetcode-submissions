class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        //frq. map
        unordered_map<int, int> frq_map;
        for (int num : nums)
            frq_map[num]++; 

        //create a min heap
        using freq_num = pair<int, int>;
        priority_queue<freq_num, vector<freq_num>, greater<freq_num>> minHeap;
        for(auto& entry : frq_map) {
            minHeap.push({entry.second, entry.first});
            if(minHeap.size() > k) 
                minHeap.pop();
        }
             
        vector<int> res; 
        for(int i=0; i<k; i++){
            res.push_back(minHeap.top().second);
            minHeap.pop();      
         }
        return res;
    }
};
