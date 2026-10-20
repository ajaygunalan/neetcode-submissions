#include <ranges>
class Solution {
public:
    int carFleet(int target, vector<int>& position, vector<int>& speed) {
        vector<pair<int, double>> cars(position.size());
        for(int i=0; i<position.size(); i++)
            cars[i] = {position[i], (double)(target-position[i])/speed[i]};
        ranges::sort(cars);

        int numOfFleets = 0;
        double lastTime = 0;
        for(auto [position, time] :  cars | views::reverse) {
            if(time <= lastTime) continue;
            else numOfFleets++, lastTime = time;
        }
        return numOfFleets;
    }
};
