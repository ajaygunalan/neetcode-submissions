class MyHashMap {
public:
    MyHashMap() {
        hashMap.assign(1000001, -1);  
    }
    
    void put(int key, int value) {
        hashMap[key] = value;
    }
    
    int get(int key) {
        return hashMap[key];
    }
    
    void remove(int key) {
        if(hashMap[key] !=  -1) hashMap[key] = -1;  
    }
private:
    vector<int> hashMap;  
};

/**
 * Your MyHashMap object will be 
 instantiated and called as such:
 * MyHashMap* obj = new MyHashMap();
 * obj->put(key,value);
 * int param_2 = obj->get(key);
 * obj->remove(key);
 */