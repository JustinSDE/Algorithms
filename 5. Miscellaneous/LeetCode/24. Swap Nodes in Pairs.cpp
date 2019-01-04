/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        ListNode dummy(0);
        dummy.next = head;
        ListNode *prevNode, *node1, *node2;
        prevNode = &dummy;
        while(true){
            node1=prevNode->next;
            if(node1==nullptr)
                break;
            node2=node1->next;
            if(node2==nullptr)
                break;
            node1->next = node2->next;
            prevNode->next = node2;
            node2->next=node1;
            prevNode = node1;
        }
        return dummy.next;
    }
};
