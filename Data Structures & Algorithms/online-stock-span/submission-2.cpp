class StockSpanner {
public:
    StockSpanner() {
        
    }
    
    int next(int price) {
        day++;
        int span=0;
        while(!st.empty() && price >= st.back().second) st.pop_back();
        if(st.empty()) span =  day;
        else span = day - st.back().first;
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