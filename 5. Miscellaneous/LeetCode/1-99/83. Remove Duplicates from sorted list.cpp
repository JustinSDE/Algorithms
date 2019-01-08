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
    ListNode* deleteDuplicates(ListNode* head) {
        if(head==nullptr)
            return head;
        ListNode* cur = head->next;
        ListNode* tail = head;
        while(cur!=nullptr){
            if(cur->val!=tail->val){
                tail->next = cur;
                tail = cur;
                cur = cur->next;
            }
            else{
                ListNode* temp = cur;
                cur = cur->next;
                delete temp;
            }
        }
        tail->next = nullptr;
        return head;
    }
};
