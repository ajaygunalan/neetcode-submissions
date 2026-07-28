/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */

class Solution {
public:
    void reorderList(ListNode* head) {
        if (!head || !head->next) return;
        //1. find the middle
        ListNode* slow = head;
        ListNode* fast = head-> next;
        while(fast && fast->next){
            slow=slow->next;
            fast=fast->next->next;
        }

        //2. cut into two list
        ListNode* second =  slow->next;
        slow->next = nullptr;
        
        //3. reverse the seocnd list
        second = reverse(second);

        //interleave tthe two halves
        merge(head, second);
    }

    ListNode* reverse(ListNode* cuurentNode) {
        if(!cuurentNode || !cuurentNode->next)
            return cuurentNode;
        
        ListNode* nextNode = cuurentNode->next;
        ListNode* reversedHead = reverse(nextNode);

        //flip the arrow
        nextNode->next = cuurentNode;
        cuurentNode->next = nullptr;
        return reversedHead;
    }

    ListNode* merge(ListNode* first, ListNode* second) {
        if (!first) return second;
        if (!second) return first;

        ListNode* firstNext = first->next;

        first->next = second;
        second->next = merge(firstNext, second->next);

        return first;
    }
};