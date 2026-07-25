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
        ListNode* reverseList(ListNode* currentNode) {
        if (currentNode == nullptr || currentNode->next == nullptr)
            return currentNode;

        // recording next node
        ListNode* nextNode = currentNode->next;

        // recurse on remaining list
        ListNode* reversedHead = reverseList(nextNode);

        //redirect the current node's next node to point at cuurent node
        nextNode->next = currentNode;

        //remove the arrow of current node
        currentNode->next = nullptr;

        return reversedHead;
        }

};