class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {

        //count the freq.
        unordered_map<int, int> frq_map;
        for (int num :  nums) {
            frq_map[num]++;
        }

        //store as fr, val
        priority_queue<pair<int, int>> maxHeap;
        for(auto p : frq_map) {
            int num = p.first;
            int frq = p.second;
            maxHeap.push({frq, num});
        }


        //take k top by fre and push into res.
        vector<int> res;
        for(int i=0; i < k; i++) {
            int num = maxHeap.top().second;
            res.push_back(num);
            maxHeap.pop();
        }
        return res;


    }
};













































    //     unordered_map<int, int> frq_map;
    //     for (int num : nums)
    //         frq_map[num]++; 

    //     //create a min heap
    //     using freq_num = pair<int, int>;
    //     priority_queue<freq_num, vector<freq_num>, greater<freq_num>> minHeap;
    //     for(auto& entry : frq_map) {
    //         minHeap.push({entry.second, entry.first});
    //         if(minHeap.size() > k) 
    //             minHeap.pop();
    //     }
             
    //     vector<int> res; 
    //     for(int i=0; i<k; i++){
    //         res.push_back(minHeap.top().second);
    //         minHeap.pop();      
    //      }
    //     return res;
    // }