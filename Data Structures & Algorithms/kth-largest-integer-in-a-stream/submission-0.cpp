#include <functional>
#include <queue>
#include <vector>

using namespace std;

class KthLargest {
private:
    priority_queue<int, vector<int>, greater<int>> minHeap;
    int k;

public:
    KthLargest(int k, vector<int>& nums) {
        this->k = k;

        // Your version: first add every initial element.
        for (int num : nums) {
            minHeap.push(num);
        }

        // Then remove the smallest values until only k remain.
        while (minHeap.size() > k) {
            minHeap.pop();
        }
    }

    int add(int val) {
        minHeap.push(val);

        // Before push, size was at most k.
        // Therefore, only one pop can be necessary.
        if (minHeap.size() > k) {
            minHeap.pop();
        }

        return minHeap.top();
    }
};