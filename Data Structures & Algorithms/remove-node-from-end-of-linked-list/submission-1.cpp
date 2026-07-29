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
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        // push nodes into array
        vector<ListNode*> nodes;
        ListNode* cur = head;
        while(cur) {
            nodes.push_back(cur);
            cur = cur->next;
        }

        int rmvIdx = nodes.size() - n;

        if(rmvIdx == 0)
            return head->next;

        nodes[rmvIdx-1]->next = nodes[rmvIdx]->next;
        return head;
        
    }
};
