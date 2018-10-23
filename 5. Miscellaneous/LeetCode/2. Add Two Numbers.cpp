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
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode dummy(-1);
        ListNode* curNode=&dummy;
        int carry=0;
        int result;
        do{
            result=(l1==nullptr?0:l1->val)+(l2==nullptr?0:l2->val)+carry;
            carry=result/10;
            result=result%10;
            if(l1){
                l1=l1->next;
            }
            if(l2)
                l2=l2->next;
            curNode->next = new ListNode(result);
            curNode=curNode->next;
        }while(l1!=nullptr || l2!=nullptr);
        if(carry!=0){
            curNode->next = new ListNode(carry);
            curNode->next->next=nullptr;
        }
        return dummy.next;
    }
};