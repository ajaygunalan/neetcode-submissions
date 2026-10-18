class MyQueue {
public:
    MyQueue() {
        
    }
    
    void push(int x) {
        pushStack.push(x);
    }
    
    int pop() {
        if(popStack.empty() ) {
            while(!pushStack.empty()) {
                int temp = pushStack.top();
                popStack.push(temp);
                pushStack.pop();
            }
        }
        int temp = popStack.top();
        popStack.pop();
        return temp;
    }
    
    int peek() {
        if(popStack.empty() ) {
            while(!pushStack.empty()) {
                int temp = pushStack.top();
                popStack.push(temp);
                pushStack.pop();
            }
        }
        return popStack.top();
    }
    
    bool empty() {
        return pushStack.empty() && popStack.empty();
    }

private:
    stack<int> pushStack, popStack;

};

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */