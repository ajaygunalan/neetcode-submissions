class StockSpanner {
public:
    StockSpanner() {
        st.push_back({0, INT_MAX});
    }
    
    int next(int price) {
        day++;
        while(!st.empty() && price >= st.back().second) st.pop_back();
        int span = day - st.back().first;
        st.push_back({day, price});   
        return span;
    }

private:
    vector<pair<int,int>> st;
    int day = 0;
};

/**
 * Your StockSpanner object will be instantiated and called as such:
 * StockSpanner* obj = new StockSpanner();
 * int param_1 = obj->next(price);
 */