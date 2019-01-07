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
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode* dummy = new ListNode(0);
        ListNode* current=dummy;
        while(l1!=nullptr && l2!=nullptr){
            if(l1->val<=l2->val){
                current->next=l1;
                current=current->next;
                l1=l1->next;
            }
            else{
                current->next=l2;
                current=current->next;
                l2=l2->next;
            }
        }
        if(l1!=nullptr){
            current->next=l1;
        }
        if(l2!=nullptr){
            current->next=l2;
        }
        current=dummy->next;
        delete dummy;
        return current;
        
    }
};
