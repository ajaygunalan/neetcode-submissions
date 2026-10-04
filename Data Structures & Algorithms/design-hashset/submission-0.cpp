class MyHashSet {
public:
    MyHashSet() {
        hashSet.assign(1000001, false);
    }
    
    void add(int key) {
        hashSet[key] = true;
    }
    
    void remove(int key) {
        hashSet[key] = false;  
    }
    
    bool contains(int key) {
        return hashSet[key];
    }
private:
    vector<bool> hashSet;
};

/**
 * Your MyHashSet object will be instantiated and called as such:
 * MyHashSet* obj = new MyHashSet();
 * obj->add(key);
 * obj->remove(key);
 * bool param_3 = obj->contains(key);
 */