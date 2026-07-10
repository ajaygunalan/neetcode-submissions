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
    ListNode* reverseList(ListNode* head) {
        //base case: empty list or final node
        if (head == nullptr || head->next == nullptr)
            return head;
        //record the next node
        ListNode* nextNode = head->next;
        //recurse on the remaining list
        ListNode* newHead = reverseList(nextNode);
        //redirect the nextNode backward
        nextNode->next =  head;
        //remove the current old arrow
        head->next = nullptr;
        
        return newHead;
    }
};